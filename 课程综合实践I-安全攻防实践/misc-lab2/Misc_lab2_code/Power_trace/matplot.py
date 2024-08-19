import numpy as np
import matplotlib.pyplot as plt
index = np.load('index.npy')
inputs = np.load('input.npy')
traces = np.load('trace.npy')
for i in range(13):
    current_traces = traces[index == i]
    current_inputs = inputs[index == i]
    mean_trace = np.mean(current_traces, axis=0)
    plt.plot(mean_trace)
    plt.title(f'第 {i+1}个字符')
    plt.show()