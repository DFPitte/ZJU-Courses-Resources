`include "core_struct.vh"
module SCPU (
  input wire clk,                       /* 时钟 */ 
  input wire rstn,                      /* 重置信号 */ 
  output wire cosim_valid,
  output wire [63:0] cosim_pc,          /* current pc */
  output wire [31:0] cosim_inst,        /* current instruction */
  output wire [ 7:0] cosim_rs1_id,      /* rs1 id */
  output wire [63:0] cosim_rs1_data,    /* rs1 data */
  output wire [ 7:0] cosim_rs2_id,      /* rs2 id */
  output wire [63:0] cosim_rs2_data,    /* rs2 data */
  output wire [63:0] cosim_alu,         /* alu out */
  output wire [63:0] cosim_mem_addr,    /* memory address */
  output wire [ 3:0] cosim_mem_we,      /* memory write enable */
  output wire [63:0] cosim_mem_wdata,   /* memory write data */
  output wire [63:0] cosim_mem_rdata,   /* memory read data */
  output wire [ 3:0] cosim_rd_we,       /* rd write enable */
  output wire [ 7:0] cosim_rd_id,       /* rd id */
  output wire [63:0] cosim_rd_data,     /* rd data */
  output wire [ 3:0] cosim_br_taken,    /* branch taken? */
  output wire [63:0] cosim_npc          /* next pc */
  );
    reg [63:0] pc;
    reg [31:0] inst;//指令
    reg [63:0] next_pc;
    reg [63:0] alu_op1, alu_op2,imm_val;
    reg [63:0]  wb_val,iinst;
    wire [63:0] alu_res;
    wire [63:0] reg_data1, reg_data2,ld_read,r_data,w_data;
    wire [4:0] rs1, rs2, rd;
    wire we_reg, we_mem, re_mem, branch_taken1, branch_taken2,jump_taken;
    wire [4:0] alu_op;
    wire [2:0] cmp_op,immgen_op, mem_op;
    wire [1:0] alu_asel, alu_bsel, wb_sel ;
    reg cosvalid,busy,memvalid,rst,jalr;
    reg flag = 0,stop;
    assign rs1 = inst[19:15];
    assign rs2 = inst[24:20];
    assign rd = inst[11:7];
    assign rst = !rstn;
    pc_upd pc_upd (
        .clk(clk),
        .rstn(rstn),
        .next_pc(next_pc),
        .pc(pc)
    );
    controller ctrl_unit (//分解指令
        .inst(inst),
        .we_reg(we_reg),
        .we_mem(we_mem),
        .re_mem(re_mem),
        .immgen_op(immgen_op),
        .is_b(branch_taken1),
        .is_j(jump_taken),
        .alu_op(alu_op),
        .cmp_op(cmp_op),
        .alu_asel(alu_asel),
        .alu_bsel(alu_bsel),
        .wb_sel(wb_sel),
        .mem_op(mem_op),
        .jalr(jalr)
    );
    ALU alu (
        .a(alu_op1),  // 选择 PC 或寄存器数据
        .b(alu_op2),  // 选择立即数或寄存器数据
        .alu_op(alu_op),//alu操作
        .res(alu_res)
    );
    //Write_sel
    write_op write(
        .clk(clk),
        .rst(rst),
        .we_mem(we_mem),
        .shift(alu_res[2:0]),
        .memop(mem_op),
        .wdata(reg_data2),
        .mem_wdata(w_data)
    );

    RAM ram(
        .clk(clk),//dmem
        .rw_wmode(we_mem),//0表示读，1表示写
        .rw_addr(alu_res[32:0]),//写入的地址
        .rw_wdata(w_data),//写入的值(寄存器中的值)
        .rw_wmask(8'b11111111),
        .rw_rdata(ld_read),//得到的值

        .ro_addr(pc[32:0]),//imem
        .ro_rdata(iinst)
    );
    read_op read(
        .clk(clk),
        .rst(rst),
        .re_mem(re_mem),
        .shift(alu_res[2:0]),
        .memop(mem_op),
        .rdata(ld_read),

        .mem_rdata(r_data)
    );
    inst_sel inst_sel (
        .in(iinst),
        .pc(pc),
        .inst(inst)
    );
    
    
    Immgen immgen (
        .inst(inst),
        .immgen_op(immgen_op),
        .imm_val(imm_val)
    );
    ALU_SEL alu_sel (
        .alu_asel(alu_asel),
        .alu_bsel(alu_bsel),
        .reg_data1(reg_data1),
        .reg_data2(reg_data2),
        .pc(pc),
        .imm_val(imm_val),
        .alu_op1(alu_op1),
        .alu_op2(alu_op2)
    );
    
    
    // 比较器实例
    Cmp cmp (
        .a(reg_data1),
        .b(reg_data2),
        .cmp_op(cmp_op),
        .cmp_res(branch_taken2)
    );
    branch_taken bt(
        .clk(clk),
        .pc(pc),
        .rstn(rstn),
        .branch_taken(branch_taken2 || jalr),
        .jump_taken(jump_taken),
        .alu_res(alu_res),
        .imm_val(imm_val),
        .next_pc(next_pc)
    );
    wb_sel Wb_sel (
        .clk(clk),
        .wb_sel(wb_sel),
        .alu_res(alu_res),
        .rdata(r_data),
        .pc(pc),
        .wb_val(wb_val)
    );
    RegFile regfile2 (//作用：读入寄存器地址，输出寄存器数据    
        .clk(clk),
        .we(we_reg),
        .read_addr_1(rs1),//读取的寄存器地址
        .read_addr_2(rs2),
        .write_addr(rd),
        .write_data(wb_val),  // 写入的数据

        .read_data_1(reg_data1),//读取的数据
        .read_data_2(reg_data2)
    );
    
    
    reg state;
    // 逐条链接到仿真输出
    assign cosim_valid = 1;
    assign cosim_pc = pc;
    assign cosim_inst =  inst;
    assign cosim_rs1_id = {3'b0, rs1};
    assign cosim_rs1_data = reg_data1;
    assign cosim_rs2_id = {3'b0, rs2};
    assign cosim_rs2_data = reg_data2;
    assign cosim_alu = alu_res;
    assign cosim_mem_addr = alu_res;
    assign cosim_mem_we = {3'b0, we_mem};
    assign cosim_mem_wdata = w_data;
    assign cosim_mem_rdata = r_data;
    assign cosim_rd_we = {3'b0, we_reg};
    assign cosim_rd_id = {3'b0, rd};
    assign cosim_rd_data = wb_val;
    assign cosim_br_taken = {3'b0,branch_taken2 || jalr};
    assign cosim_npc = next_pc;
endmodule
