# OOP-criminal-record-system
OOP project 

#### modification -will be modified on 11/27
1. 紅黑數的 `Node` 改成直接使用 `CrimeRecord` 作為節點
2. 每一個 `CrimeRecord` Node 新增兩個 attributes: 
* `CrimeRecord->parent` , `CrimeRecord->color`
  
3. 每一個 `CrimeRecord` Node 刪除兩個 attributes:
* `CrimeRecord->left`, `CrimeRecord->right`

4. `Criminal` class 改成使用 `vector<CrimeRecord>` 儲存 `CrimeRecord` objects, 捨棄 doubly linked-list

查找時間從原本的時間複雜度 `O(lgn + m)` 變為 `O(lgn)` 
