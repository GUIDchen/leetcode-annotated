// 题目：2718. 查询后矩阵的和（Sum of Matrix After Queries）
// 思路：从后往前看查询，每个位置只由最后一次覆盖它的查询决定；用集合记录已被后面查询占用的行与列，跳过重复行/列即可。
// 时间复杂度：O(n+q)，q 为查询数，每行只处理一次；空间复杂度：O(n)，两个集合最多各存 n 个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long matrixSumQueries(int n, vector<vector<int>>& queries) {  // n 为矩阵边长，queries 为 [类型, 下标, 值] 的覆盖操作列表
        unordered_set<int> row, col;  // row、col 分别记录已经被「更晚的查询」覆盖过的行号与列号
        reverse(queries.begin(), queries.end());  // 倒序处理，这样每个位置最后一次被赋的值会最先确定
        long long ans = 0;  // ans：最终矩阵元素和，可能超过 32 位所以用 long long
        for (auto& q : queries) {  // 逐个处理倒序后的查询
            int t = q[0], i = q[1], v = q[2];  // t 为类型（0 整行、1 整列），i 为下标，v 为赋的值
            if (t == 0) {  // 类型 0：把第 i 行整行赋成 v
                if (!row.count(i)) {  // 该行之前没被更晚的查询覆盖过，这次才真正生效
                    ans += 1LL * (n - col.size()) * v;  // 生效格子数为 n 减去已被后面覆盖的列数，乘上 v 累加
                    row.insert(i);  // 标记这一行已被占用，更早的行查询不再生效
                }
            } else {  // 类型 1：把第 i 列整列赋成 v
                if (!col.count(i)) {  // 该列之前没被更晚的查询覆盖过，这次才真正生效
                    ans += 1LL * (n - row.size()) * v;  // 生效格子数为 n 减去已被后面覆盖的行数，乘上 v 累加
                    col.insert(i);  // 标记这一列已被占用，更早的列查询不再生效
                }
            }
        }
        return ans;  // 返回倒序累加得到的矩阵元素总和
    }
};