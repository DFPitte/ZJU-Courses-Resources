import urllib.parse

with open("data.txt", "r") as file:
    lines = file.readlines()
st = [] # 存储提取出的数据
seen = set() 

for i in range(627, 972):
    data = urllib.parse.unquote(lines[i]).strip()
    
    payload = data.split("and")[1]
    positions = payload.find("from db_flag.tb_flag  limit 0,1)) ")

    extracted_data = payload[positions + 35:].split(",")
    data1 = extracted_data[0]
    data2 = extracted_data[1].split(">")[1]
    
    if data1 not in seen:  
        st.append([data1, data2])
        seen.add(data1)

for i in range(1, len(st)):
    if st[i][0] != st[i - 1][0]:
        print(chr(int(st[i - 1][1])), end="")
print(chr(int(st[-1][1])))