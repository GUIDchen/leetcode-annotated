// 题目：2386. 找出数组的第 K 大和（Find the K-Sum of an Array）
// 核心思路：先求所有正数之和 mx（即第 1 大和），把负数取绝对值后排序，问题转化为求「第 k-1 小的子集和」，用最小堆按「选/不选当前数」递推弹出，答案即 mx - 该子集和。
// 时间复杂度：O(n log n + k log k)，排序加 k 次堆操作；空间复杂度：O(n + k)，存放取绝对值后的数组与堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long kSum(vector<int>& nums, int k) {  // nums：输入数组；k：要求的第 k 大子集和；返回值可能超过 int 范围
        long long mx = 0;  // mx 记录所有正数之和，即所有子集和中的最大值（第 1 大和）
        int n = nums.size();  // 先缓存数组长度，后面多次使用
        for (int i = 0; i < n; ++i) {  // 逐个处理数组元素，拆出正数与负数两条分支
            if (nums[i] > 0) {  // 正数直接计入最大和
                mx += nums[i];  // 累加这个正数
            } else {  // 否则该元素不是正数，需要取绝对值参与「减少量」的计算
                nums[i] *= -1;  // 取绝对值：选中负元素等价于从 mx 中减去 |nums[i]|
            }  // 结束正负判断
        }  // 结束遍历
        sort(nums.begin(), nums.end());  // 按绝对值升序排序，保证堆里能按「从小到大让步」的顺序枚举子集和
        using pli = pair<long long, int>;  // 给 pair<long long, int> 起别名：first 是当前子集和，second 是下一个待决策的下标
        priority_queue<pli, vector<pli>, greater<pli>> pq;  // 小根堆：每次弹出当前最小的子集和，从而依次得到第 1 小、第 2 小……
        pq.push({0, 0});  // 初始状态：和为 0，从下标 0 开始决策，对应「什么都不选」
        while (--k) {  // 循环 k-1 次，把最小的 k-1 个子集和依次弹出，堆顶就是第 k 小的子集和
            auto p = pq.top();  // 取出堆顶（当前最小的子集和状态）
            pq.pop();  // 弹出堆顶
            long long s = p.first;  // s 是当前累计的子集和
            int i = p.second;  // i 是接下来要处理的下标
            if (i < n) {  // 下标越界说明没有更多元素可选，这个状态不再扩展
                pq.push({s + nums[i], i + 1});  // 扩展一：选上 nums[i]，子集和增加 nums[i]
                if (i) {  // i 非 0 才存在「把上一个已选的数换成 nums[i]」这种扩展
                    pq.push({s + nums[i] - nums[i - 1], i + 1});  // 扩展二：把原来选中的 nums[i-1] 替换成 nums[i]，即补偿二者之差
                }  // 结束内层 if
            }  // 结束下标合法性判断
        }  // 结束弹出循环
        return mx - pq.top().first;  // 第 k 大和 = mx 减去第 k-1 小的「减少量」
    }  // 结束方法体
};  // 结束题解类