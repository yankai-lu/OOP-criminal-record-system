# OOP-criminal-record-system
OOP project 


1. `Criminal` class 改成使用 `vector<CrimeRecord>` 儲存 `CrimeRecord` objects, 捨棄 doubly linked-list

查找時間從原本的時間複雜度 `O(lgn + m)` 變為 `O(lgn)` 


### Adding searching functions in Red Black Tree
1. Search based on `time` only
2. Search based on an `interval of time` only
3. Search based on `time` and `type of crime`
4. Search based on `an interval of time` and `type of crime`
5. Search based on `criminal's name`


### System class
1. 負責將新產生的 CrimeRecord 節點與 Criminal object 連結再一起 (UML)
2. 使用 Red Black Trees 查找資料並輸出結果 (搜尋功能在 Red Black Tree已經寫好，只需要呼叫 Red Black Tree 內對應的 functions 即可)

### GUI 



### Program執行
使用VScode時，編譯器路徑有可能與我們的不一樣，需自行修改.vscode資料夾中的環境參數
1.  ctrl + shift + p → 搜尋「C/C++: Edit Configurations (JSON)」
2.  新增 "includePath" 後的地址
3.  更改 "compiler path" 後的地址
4.  更改 "intelliSenseMode" 為您的OS類型
