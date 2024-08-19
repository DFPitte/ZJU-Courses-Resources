`include "core_struct.vh"

module controller (
    input CorePack::inst_t inst,
    output reg we_reg,
    output reg we_mem,
    output reg re_mem,
    output reg is_b,
    output reg is_j,
    output CorePack::imm_op_enum immgen_op,
    output CorePack::alu_op_enum alu_op,
    output CorePack::cmp_op_enum cmp_op,
    output CorePack::alu_asel_op_enum alu_asel,
    output CorePack::alu_bsel_op_enum alu_bsel,
    output CorePack::wb_sel_op_enum wb_sel,
    output CorePack::mem_op_enum mem_op,
    output jalr
);

    import CorePack::*;
    // First stage decoding
    wire [6:0] opcode = inst[6:0];//
    wire [2:0] funct3 = inst[14:12];
    wire [6:0] funct7 = inst[31:25];
    // Second stage decoding
    wire r_type = (opcode == 7'b0110011 || opcode == REGW_OPCODE);
    wire i_type = (opcode == 7'b0010011 || opcode == 7'b0000011 || opcode == 7'b1100111 || opcode ==IMMW_OPCODE);
    wire s_type = (opcode == 7'b0100011);
    wire b_type = (opcode == 7'b1100011);
    wire u_type = (opcode == 7'b0110111 || opcode == 7'b0010111);
    wire j_type = (opcode == 7'b1101111);
    wire addw = (opcode == IMMW_OPCODE);  
    wire regw = (opcode == REGW_OPCODE);
    assign jalr = (opcode == 7'b1100111);
    always_comb begin
        we_reg = r_type | i_type | u_type | j_type ;//这四种类型的指令会写寄存器
        we_mem = s_type;//Store指令会写内存
        re_mem = (opcode == 7'b0000011);//Load指令会读内存
        is_b = b_type || jalr;//Branch指令
        is_j = j_type ;//Jump指令

        // 生成立即数指令
        case (opcode)
            IMMW_OPCODE,IMM_OPCODE,LOAD_OPCODE: immgen_op = I_IMM;//Itype
            7'b0100011: immgen_op = S_IMM;//Stype
            7'b1100011: immgen_op = B_IMM;//Btype
            7'b0110111, 7'b0010111: immgen_op = U_IMM;
            7'b1101111: immgen_op = UJ_IMM;
            default: immgen_op = IMM0;
        endcase

        // ALU operation
        if (r_type || i_type || u_type) begin
            if(r_type)begin
                if(regw)begin
                    case (funct3)
                        3'b000: alu_op = (funct7 == 7'b0100000)? ALU_SUBW: ALU_ADDW;
                        3'b001: alu_op = ALU_SLLW;
                        3'b101: alu_op = (funct7[5] == 0) ? ALU_SRLW : ALU_SRAW;

                        default: alu_op = ALU_DEFAULT;
                    endcase
                end
                else begin
                case (funct3)
                    3'b000: alu_op = (funct7 == 7'b0100000)? ALU_SUB: ALU_ADD;
                    3'b001: alu_op = ALU_SLL ; // For SLL in R-Type
                    3'b010: alu_op = ALU_SLT;
                    3'b011: alu_op = ALU_SLTU;
                    3'b100: alu_op = ALU_XOR;
                    3'b101: alu_op = (funct7[5] == 0) ? ALU_SRL : ALU_SRA;
                    3'b110: alu_op = ALU_OR;
                    3'b111: alu_op = ALU_AND;

                    default: alu_op = ALU_DEFAULT;
                endcase
                end
            end
            else if(i_type) begin
                if(opcode == 7'b0000011)
                alu_op = ALU_ADD;
                else if (addw)begin
                    case (funct3)
                        3'b000: alu_op = ALU_ADDW;
                        3'b001: alu_op = ALU_SLLW;
                        3'b101: alu_op = (funct7[5] == 0) ? ALU_SRLW : ALU_SRAW;
                        default: alu_op = ALU_DEFAULT;
                    endcase
                end
                else begin
                case (funct3)
                    3'b000: alu_op = ALU_ADD;
                    3'b001: alu_op = ALU_SLL;
                    3'b010: alu_op = ALU_SLT;
                    3'b011: alu_op = ALU_SLTU;
                    3'b100: alu_op = ALU_XOR;
                    3'b101: alu_op = (funct7[5] == 0) ? ALU_SRL : ALU_SRA;
                    3'b110: alu_op = ALU_OR;
                    3'b111: alu_op = ALU_AND;
                    default: alu_op = ALU_DEFAULT;
                endcase
                end
            end
            else if(u_type) begin
                alu_op = (opcode == 7'b0110111) ? ALU_LUI : ALU_AUIPC;
            end
            else if(j_type) begin
                alu_op = ALU_ADD;
            end
            else begin
                alu_op = ALU_DEFAULT;
            end
        end
    
        // ALU A select
        alu_asel = (b_type | j_type | u_type) ? ASEL_PC : ASEL_REG;

        // ALU B select
        alu_bsel = (i_type | s_type | b_type | j_type| u_type) ? BSEL_IMM : BSEL_REG;

        // Write-back select
        wb_sel = (opcode == 7'b0000011 && i_type) ? WB_SEL_MEM :
             (r_type || i_type || u_type || s_type) ? WB_SEL_ALU :
             (j_type) ? WB_SEL_PC : WB_SEL0;
        // Memory operation
        if(jalr)wb_sel = WB_SEL_PC;
        if(opcode == 7'b0000011)begin
            case (funct3)
                3'b000: mem_op = MEM_B;
                3'b001: mem_op = MEM_H;
                3'b010: mem_op = MEM_W;
                3'b011: mem_op = MEM_D;
                3'b100: mem_op = MEM_UB;
                3'b101: mem_op = MEM_UH;
                3'b110: mem_op = MEM_UW;
                default: mem_op = MEM_NO;
            endcase
        end
        if(s_type)begin
            alu_op = ALU_ADD;
            case (funct3)
                3'b000: mem_op = MEM_B;
                3'b001: mem_op = MEM_H;
                3'b010: mem_op = MEM_W;
                3'b011: mem_op = MEM_D;
                default: mem_op = MEM_NO;
            endcase
        end
        // Branch comparison operation
        if (b_type) begin
            alu_op = ALU_ADD;
            case (funct3)
                3'b000: cmp_op = CMP_EQ;
                3'b001: cmp_op = CMP_NE;
                3'b100: cmp_op = CMP_LT;
                3'b101: cmp_op = CMP_GE;
                3'b110: cmp_op = CMP_LTU;
                3'b111: cmp_op = CMP_GEU;
                default: cmp_op = CMP_NO;
            endcase
        end
        else begin
            cmp_op = CMP_NO;
        end
        
        end
endmodule
