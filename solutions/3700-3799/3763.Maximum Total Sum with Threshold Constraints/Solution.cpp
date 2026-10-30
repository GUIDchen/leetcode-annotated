// 3763. 带阈值约束的最大总和 / Maximum Total Sum with Threshold Constraints
// 核心思路：按下标对应的 threshold 升序排序，用有序多重集合维护“已解锁”的分数，每一步取出其中的最大值累加。
// 复杂度：时间 O(n log n)，空间 O(n)。
class Solution {  // 定义解法类
public:  // 公有方法区
    long long maxSum(vector<int>& nums, vector<int>& threshold) {  // 求最大总和：nums 为可获得的分数，threshold 为元素最早可用的步数
        int n = nums.size();  // 元素个数
        vector<int> idx(n);  // 下标数组，用于按阈值排序
        iota(idx.begin(), idx.end(), 0);  // 填入 0..n-1 的下标
        sort(idx.begin(), idx.end(), [&](int a, int b) { return threshold[a] < threshold[b]; });  // 按各下标对应的 threshold 升序排序

        multiset<int> ms;  // 有序多重集合，保存当前可选的分数
        long long ans = 0;  // 答案累加器
        int i = 0;  // 下一个待加入集合的元素指针

        for (int step = 1;; ++step) {  // 从第 1 步开始逐步推进，每步取走一个分数
            while (i < n && threshold[idx[i]] <= step) {  // 把 threshold 已到达当前步数的元素全部解锁
                ms.insert(nums[idx[i]]);  // 把该元素的分数插入集合
                ++i;  // 指针后移
            }
            if (ms.empty()) {  // 集合为空说明已无元素可解禁，无法继续
                break;  // 提前结束循环
            }

            auto it = prev(ms.end());  // 指向集合中的最大分数
            ans += *it;  // 累加当前能取到的最大值
            ms.erase(it);  // 删除已经被使用的元素
        }
        return ans;  // 返回最大总和
    }  // 方法结束
};  // 类结束
