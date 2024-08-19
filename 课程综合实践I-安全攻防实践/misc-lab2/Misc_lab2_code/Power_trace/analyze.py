import numpy as np
 
# 加载数据集
index = np.load("index.npy")
inputs = np.load("input.npy")
outputs = np.load("output.npy")
traces = np.load("trace.npy")
 
# 假设我们有13个密码字符需要预测
num_characters = 13
character_length = 40  # 每个字符对应的迹象数量
 
password = []
# 遍历每个密码字符
for character_index in range(num_characters):
    time_min_indices = []
    # 获取当前字符对应的输入和迹象
    current_inputs = inputs[character_length * character_index : character_length * (character_index + 1)]
    current_traces = traces[character_length * character_index : character_length * (character_index + 1)]
    #print(current_traces)
    # 对每个迹象，找到功耗最小的时间点
    for trace in current_traces:
        min_time_index = np.argmin(trace)
        time_min_indices.append(min_time_index)
 
    # 找到最显著的迹象（最小功耗出现最晚的那个）
    most_significant_trace_index = np.argmax(time_min_indices)
    # 获取对应的输入字符
    predicted_character = current_inputs[most_significant_trace_index]
    print(predicted_character)
    password.append(predicted_character)
 
for char in password:
    print(char, end="")