// 3690. Split and Merge Array Transformation（3690. 拆分合并数组）
// 核心思路：一次操作 = 取出任意子数组再插回任意位置；把整个数组当作 BFS 的状态（set 去重、vector 作哈希键），从 nums1 逐层扩展，第一次遇到 nums2 时的层数就是最少操作数。
// 复杂度：时间 O(V × n^3)（V 为可达状态数，每个状态枚举 O(n^2) 个区间 × O(n) 个插入点），空间 O(V × n)。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {  // 主函数：求把 nums1 变成 nums2 所需的最少“拆分合并”次数
        int n = nums1.size();  // n 为数组长度
        vector<int> target = nums2;  // 目标数组，逐层比较时使用
        vector<vector<int>> q{nums1};  // BFS 队列，初始状态就是 nums1
        set<vector<int>> vis;  // 访问集合，记录已经入队过的数组（vector 可直接作哈希键）
        vis.insert(nums1);  // 起始状态标记为已访问

        for (int ans = 0;; ++ans) {  // 按层递增枚举操作次数，ans 即当前层数
            vector<vector<int>> t = q;  // 取出当前层的全部状态
            q.clear();  // 清空队列，用来装下一层状态
            for (auto& cur : t) {  // 逐个处理当前层里的状态
                if (cur == target) {  // 当前状态已经等于目标数组
                    return ans;  // 当前层数就是最少操作数，直接返回
                }  // if 分支结束
                for (int l = 0; l < n; ++l) {  // 枚举被取出的子数组左端点 l
                    for (int r = l; r < n; ++r) {  // 枚举子数组右端点 r，子数组即 [l, r]
                        vector<int> remain;  // remain 保存摘掉子数组后剩下的部分
                        remain.insert(remain.end(), cur.begin(), cur.begin() + l);  // 先拼上子数组左侧的元素
                        remain.insert(remain.end(), cur.begin() + r + 1, cur.end());  // 再拼上子数组右侧的元素
                        vector<int> sub(cur.begin() + l, cur.begin() + r + 1);  // sub 是取出的子数组 [l, r]
                        for (int i = 0; i <= (int) remain.size(); ++i) {  // 枚举把 sub 插回 remain 的位置 i，共 remain.size()+1 个空位
                            vector<int> nxt;  // nxt 表示一次操作得到的新数组
                            nxt.insert(nxt.end(), remain.begin(), remain.begin() + i);  // 先放入 remain 的前 i 个元素
                            nxt.insert(nxt.end(), sub.begin(), sub.end());  // 把取出的子数组 sub 插入此处
                            nxt.insert(nxt.end(), remain.begin() + i, remain.end());  // 再放入 remain 剩下的元素

                            if (!vis.count(nxt)) {  // 只有没访问过的状态才入队
                                vis.insert(nxt);  // 标记该状态已访问
                                q.push_back(nxt);  // 加入下一层队列
                            }  // if 分支结束
                        }  // 插入位置枚举结束
                    }  // 右端点枚举结束
                }  // 左端点枚举结束
            }  // 当前层遍历结束
        }  // 层数递增循环结束（BFS 一定会在有限状态内返回，此处不会真正死循环）
    }  // 主函数结束
};  // 类定义结束
