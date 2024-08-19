`include "core_struct.vh"

module ALU (
  input  CorePack::data_t a,
  input  CorePack::data_t b,
  input  CorePack::alu_op_enum  alu_op,
  output CorePack::data_t res
);

  import CorePack::*;

  data_t result; // 存放 ALU 的计算结果
  wire i;
  reg [31:0] tmp,sllw,sraw,subw,srlw;
  assign tmp = a[31:0] + b[31:0];
  assign subw = a[31:0] - b[31:0];
  assign sllw = a[31:0] << b[4:0];
  assign srlw = a[31:0] >> b[4:0];
  assign sraw = $signed(a[31:0]) >>> b[4:0];
  always @* begin
    
    case (alu_op)
      
      ALU_ADD: result = a + b;
      ALU_SUB: result = a - b;
      ALU_AND: result = a & b;
      ALU_OR: result = a | b;
      ALU_XOR: result = a ^ b;
      ALU_SLT: begin
        if(a == 0 && b ==-1)result = 0;
        else if (a == -1 && b == 0)result = 1;
        else result = (a < b) ? 1 : 0;
      end
      ALU_SLTU: result = (a < b) ? 1 : 0; // 无符号比较
      ALU_SLL: result = a << b[5:0];
      ALU_SRL: result = a >> b[5:0];
      ALU_SRA: begin 
        result = $signed(a) >>> b[5:0]; 
      end
      ALU_ADDW: begin
        result = {{32{tmp[31]}},tmp[31:0]};
      end
      ALU_SUBW: result = {{32{subw[31]}},subw[31:0]};
      ALU_SLLW: result = {{32{sllw[31]}},sllw[31:0]};
      ALU_SRLW: result = {{32{srlw[31]}},srlw[31:0]};
      ALU_SRAW: begin 
         result = {{32{sraw[31]}},sraw[31:0]};
      end
      ALU_LUI: result = {{32{b[63]}},b[63:32]};
      ALU_AUIPC: result = a + {{32{b[63]}}, b[63:44], 12'b0};
      default: result = 0; // 默认情况下，输出0
    endcase
    //$display("ALU: a=%h, b=%h, alu_op=%b,alu_res=%h\n", a, b, alu_op,result);
  end
  assign res = result; // 将结果输出

endmodule
