// 题目：2201. 统计可以提取的工件（Count Artifacts That Can Be Extracted）
// 思路：把已挖开的格子用「行*n+列」压成一维整数存进哈希集合，再逐个工件枚举它覆盖的每个格子，全部在集合中才能提取。
// 时间复杂度：O(d + 工件总面积)，每个挖开的格子与每个工件格子都只访问一次；空间复杂度：O(d)，哈希集合存 d 个格子编号。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {  // n：网格边长；artifacts：每个工件的左上/右下角坐标；dig：已经挖开的格子
        unordered_set<int> s;  // 哈希集合：保存已挖开格子的编号，支持 O(1) 查询
        for (auto& p : dig) {  // 遍历所有被挖开的格子
            s.insert(p[0] * n + p[1]);  // 编号 = 行 * n + 列，把二维坐标压成一维整数，避免自己写哈希
        }  // 结束挖开格子的遍历
        auto check = [&](vector<int>& a) {  // 局部 lambda：判断某个工件是否每一格都已被挖开；[&] 按引用捕获外部的 s 和 n
            int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3];  // 拆出工件的左上角 (x1, y1) 与右下角 (x2, y2)
            for (int x = x1; x <= x2; ++x) {  // 逐行遍历工件覆盖的范围
                for (int y = y1; y <= y2; ++y) {  // 逐列遍历这一行内的格子
                    if (!s.count(x * n + y)) {  // 只要有一个格子还没被挖开
                        return 0;  // 该工件不能提取，直接返回 0（方便后面直接累加到答案上）
                    }  // 结束 if
                }  // 结束列循环
            }  // 结束行循环
            return 1;  // 所有格子都已挖开，该工件可以提取
        };  // 结束 lambda 定义
        int ans = 0;  // 记录可提取的工件数量
        for (auto& a : artifacts) {  // 逐个工件做检查
            ans += check(a);  // check 返回 0/1，直接累加即可完成计数
        }  // 结束工件循环
        return ans;  // 返回可以提取的工件数
    }  // 结束方法
};  // 结束 Solution 类