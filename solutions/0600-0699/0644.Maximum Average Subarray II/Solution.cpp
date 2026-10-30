// 题目：644. 子数组最大平均数 II（Maximum Average Subarray II）
// 核心思路：二分答案 v，把每个元素减去 v 后，判断是否存在长度 ≥ k 且和 ≥ 0 的子数组；判断时用滚动窗口和 s 与「可裁前缀和的最小值 mi」在 O(n) 内完成。
// 时间复杂度：O(n log((max-min)/eps))；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double findMaxAverage(vector<int>& nums, int k) {  // nums：输入数组；k：子数组长度的下界
        double eps = 1e-5;  // 二分精度，题目允许 1e-5 的误差
        double l = *min_element(nums.begin(), nums.end());  // 答案下界：数组最小值
        double r = *max_element(nums.begin(), nums.end());  // 答案上界：数组最大值
        auto check = [&](double v) {  // 判断是否存在长度 ≥ k、平均值 ≥ v 的子数组
            double s = 0;  // 当前长度恰好为 k 的窗口和（每个元素都已减去 v）
            for (int i = 0; i < k; ++i) {  // 先算前 k 个元素减 v 后的和
                s += nums[i] - v;  // 把「平均值 ≥ v」转化为「窗口和 ≥ 0」
            }  // 初始窗口构造完成
            if (s >= 0) {  // 前 k 个元素就满足条件
                return true;  // 存在合法子数组
            }  // 否则继续向右扩展窗口
            double t = 0;  // 从窗口左端开始、可随时裁掉的前缀和
            double mi = 0;  // t 的最小值，用来找最该被裁掉的那段前缀
            for (int i = k; i < nums.size(); ++i) {  // 窗口右端右移
                s += nums[i] - v;  // 窗口和加上新右端
                t += nums[i - k] - v;  // 把被移出窗口的那个元素累进前缀和
                mi = min(mi, t);  // 维护前缀和的最小值
                if (s >= mi) {  // 去掉最小值那段前缀后仍非负，说明存在更长且达标的子数组
                    return true;  // 存在合法子数组
                }  // 否则继续右移
            }  // 窗口扫到末尾
            return false;  // 不存在平均值 ≥ v 的合法子数组
        };  // lambda 定义结束
        while (r - l >= eps) {  // 二分直到区间足够小
            double mid = (l + r) / 2;  // 取区间中点
            if (check(mid)) {  // 中点可行，答案在右半边
                l = mid;  // 抬高下界
            } else {  // 中点不可行，答案在左半边
                r = mid;  // 压低上界
            }  // 继续二分
        }  // 二分结束
        return l;  // 返回收敛后的下界，即最大平均数
    }  // 方法结束
};  // 类结束