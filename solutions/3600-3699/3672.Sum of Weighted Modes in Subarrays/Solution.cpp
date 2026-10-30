// 3672. Sum of Weighted Modes in Subarrays（子数组中加权众数的总和）
// 核心思路：哈希表维护窗口内频次，大顶堆按 (频次, 值) 取众数，堆顶频次过期就弹出，滑动窗口逐个累加众数权重。
// 复杂度：时间 O(n log n)，空间 O(n)。
class Solution {  // 定义 Solution 类
public:
    long long modeWeight(vector<int>& nums, int k) {  // 求所有长度为 k 的子数组的加权众数之和
        unordered_map<int, int> cnt;  // 记录当前窗口内每个值的出现次数
        priority_queue<pair<int, int>> pq; // {freq, -val} 按 (频次, 值) 维护的大顶堆：频率高者优先，同频时值小者优先

        for (int i = 0; i < k; i++) {  // 初始化长度为 k 的第一个窗口
            int x = nums[i];  // 当前元素
            cnt[x]++;  // 该值的频次加一
            pq.push({cnt[x], -x});  // 把最新的 (频次, -值) 压入堆
        }

        auto get_mode = [&]() {  // 定义取当前窗口加权众数的 lambda
            while (true) {  // 不断弹出已被更新覆盖的过期堆顶
                auto [freq, negVal] = pq.top();  // 取出堆顶的频次与取负后的值
                int val = -negVal;  // 还原真实的值
                if (cnt[val] == freq) {  // 堆顶频次与哈希表一致，说明是最新记录
                    return 1LL * freq * val;  // 返回加权众数，1LL 避免乘法溢出
                }
                pq.pop();  // 否则该堆顶已过期，弹出
            }
        };

        long long ans = 0;  // 累加每个长度为 k 的子数组的加权众数
        ans += get_mode();  // 加上第一个窗口的贡献

        for (int i = k; i < nums.size(); i++) {  // 窗口右移，处理每个新进入的元素
            int x = nums[i], y = nums[i - k];  // x 为新进入的元素，y 为滑出的元素
            cnt[x]++;  // 新元素频次加一
            cnt[y]--;  // 滑出元素频次减一
            pq.push({cnt[x], -x});  // 把新元素的当前频次入堆
            pq.push({cnt[y], -y});  // 把滑出元素的当前频次入堆
            ans += get_mode();  // 累加当前窗口的加权众数
        }

        return ans;  // 返回加权众数的总和
    }
};
