import cffi

ffi = cffi.FFI()

# 定義與 C++ 函數相符的接口
ffi.cdef("""
    int main(void);
""")

# 加載共享庫
mylib = ffi.dlopen('mylib.dll')

# 調用函數
result = mylib.main()
if result == 0:
    print("結束程式，成功退出")
else:
    print("發生錯誤")
