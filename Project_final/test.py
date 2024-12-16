import cffi

ffi = cffi.FFI()

# 定義與 C++ 函數相符的接口
ffi.cdef("""
    int main(void);
""")

ffi.cdef("""
    void test(char** array, int row, int col);
""")

# 加載共享庫
mylib = ffi.dlopen('mylib.dll')

row = 100     # result array size
col = 100
responce = [] # result array

for i in range(row):
    line = ffi.new(f"char[{col}]")  # 每行的數組
    responce.append(line)

# 創建二維指針陣列
responce_ptr = ffi.new(f"char*[{row}]", responce)    # result array pointer

mylib.test(responce_ptr, row, col)

# 將數據拷貝回 Python 列表
for i in range(row):
    print(ffi.string(responce[i]).decode("utf-8"))

# 調用函數
'''
result = mylib.main()
if result == 0:
    print("結束程式，成功退出")
else:
    print("發生錯誤")
'''
