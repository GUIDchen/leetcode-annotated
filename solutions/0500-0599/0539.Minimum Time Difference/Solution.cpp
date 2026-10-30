// 题目：539. 最小时间差（Minimum Time Difference）
// 思路：把每个 "HH:MM" 转成当天的分钟数并排序，最小差值只可能出现在相邻两项之间；再把首项 +1440 接到末尾以处理跨零点的环形差值。
// 时间复杂度：O(n log n)，瓶颈是排序；空间复杂度：O(n)，存放转换后的分钟数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMinDifference(vector<string>& timePoints) {  // timePoints 是若干 "HH:MM" 形式的时间点，返回两两之间的最小分钟差
        if (timePoints.size() > 1440) {  // 一天只有 1440 分钟：若时间点超过 1440 个，由抽屉原理必然有重复，最小差为 0
            return 0;  // 存在重复时间点，直接返回 0
        }
        int n = timePoints.size();  // n 是时间点个数，后面反复使用
        vector<int> nums(n + 1);  // 多开一个位置，用来放「首项 +1440」这个环形哨兵
        for (int i = 0; i < n; ++i) {  // 逐个时间点解析成当天的分钟数
            int hours = stoi(timePoints[i].substr(0, 2));  // 取前两位作为小时，stoi 把字符串转成整数
            int minutes = stoi(timePoints[i].substr(3, 2));  // 取第 4、5 位的两位数字作为分钟（下标 3 处是冒号）
            nums[i] = hours * 60 + minutes;  // 换算成从 00:00 起算的分钟数，写入数组
        }
        sort(nums.begin(), nums.begin() + n);  // 只对前 n 个真实数据排序，哨兵位置仍留空
        nums[n] = nums[0] + 1440;  // 环形处理：末尾补上「首项 + 一天的分钟数」，表示跨过零点的那个时间点
        int ans = INT_MAX;  // ans 记录当前找到的最小差值，初始为最大整数
        for (int i = 1; i <= n; ++i) {  // 依次比较每一对相邻分钟数（包含末尾的环形哨兵）
            ans = min(ans, nums[i] - nums[i - 1]);  // 用相邻差更新答案，排序后最小差必然取在相邻两项之间
        }
        return ans;  // 返回最小时间差
    }
};