// 题目：659. 分割数组为连续子序列（Split Array into Consecutive Subsequences）
// 核心思路：贪心，用哈希表把「尾部值」映射到「以小根堆存的各序列长度」，每个数优先接到最短的、以 v-1 结尾的序列后。
// 时间复杂度：O(n log n)（每次堆操作）；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:
    bool isPossible(vector<int>& nums) {  // nums 已升序，判断能否切成若干长度不少于 3 的连续子序列
        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> d;  // d[尾部值] = 小根堆，存放以该值结尾的各条子序列长度
        for (int v : nums) {  // 按升序依次处理每个数字
            if (d.count(v - 1)) {  // 若能接到以 v-1 结尾的某条序列后面，就优先接
                auto& q = d[v - 1];  // 取出以 v-1 结尾的长度堆（引用，避免拷贝整堆）
                d[v].push(q.top() + 1);  // 从堆里弹出一个最短长度接上 v，新长度存入以 v 结尾的堆
                q.pop();  // 这条序列已经离开 v-1 这一组
                if (q.empty()) {  // 这个尾部值已经没有序列了
                    d.erase(v - 1);  // 清掉空条目，保证 d.count(v-1) 的语义正确
                }
            } else {  // 接不上任何已有序列，只能让 v 作为新序列的开头
                d[v].push(1);  // 新序列长度为 1
            }
        }
        for (auto& [_, v] : d) {  // 检查所有收尾的序列长度是否都达标
            if (v.top() < 3) {  // 堆顶就是这条尾巴上最短的序列长度
                return false;  // 存在长度小于 3 的序列，无法满足题意
            }
        }
        return true;  // 全部合格，返回 true
    }
};  // 题解类定义结束