`timescale 1ns / 1ps

module SegDecoder (
    input wire [3:0] data,  // 要显示的十六进制数
    input wire point,       // 是否显示小数点，0 显示小数点
    input wire LE,          // 是否使能，0 使能

    output wire a,          
    output wire b,          
    output wire c,          
    output wire d,          
    output wire e,          
    output wire f,          
    output wire g,          
    output wire p           // 小数点对应的数码管
);

// 若LE为高，则关闭所有段（即不显示任何内容）
//assign {a, b, c, d, e, f, g} = LE? 7'b1111111 : decoded[data];

// 使用一个8位宽的寄存器数组来存储每个十六进制数字对应的七段数码管编码
// 0表示亮，1表示灭。最低位用于小数点，这里始终将其设为1，因为小数点的控制由point信号单独处理
reg [6:0] decoded[0:15];

initial begin
    // 初始化十六进制数字到7段LED的映射
    // 由于是负逻辑，所以亮为0，灭为1
    
    decoded[0]  = 7'b0000001; // 0
    decoded[1]  = 7'b1001111; // 1
    decoded[2]  = 7'b0010010; // 2
    decoded[3]  = 7'b0000110; // 3
    decoded[4]  = 7'b1001100; // 4
    decoded[5]  = 7'b0100100; // 5
    decoded[6]  = 7'b0100000; // 6
    decoded[7]  = 7'b0001111; // 7
    decoded[8]  = 7'b0000000; // 8
    decoded[9]  = 7'b0000100; // 9
    decoded[10] = 7'b0001000; // A
    decoded[11] = 7'b1100000; // b
    decoded[12] = 7'b0110001; // C
    decoded[13] = 7'b1000010; // d
    decoded[14] = 7'b0110000; // E
    decoded[15] = 7'b0111000; // F
end
assign {a, b, c, d, e, f, g} = LE? 7'b1111111 : decoded[data];
endmodule
