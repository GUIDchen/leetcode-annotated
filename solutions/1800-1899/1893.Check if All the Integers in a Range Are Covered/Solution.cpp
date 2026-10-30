// 题目：1893. 检查是否区域内所有整数都被覆盖（Check if All the Integers in a Range Are Covered）
// 思路：用差分数组统计每个整数被多少个区间覆盖，前缀和即为该点的覆盖数；只要 [left, right] 内某点覆盖数为 0 就返回 false。
// 时间复杂度：O(n + 50)，n 为区间个数；空间复杂度：O(50)，差分数组长度固定为 52。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {  // ranges：给定区间集合；left、right：待检查的目标区间（数值范围 1..50）
        vector<int> diff(52);  // 差分数组，下标 0..51 足以容纳 1..50 的所有端点及其 +1
        for (auto& range : ranges) {  // 遍历每个给定区间，做差分标记
            int l = range[0], r = range[1];  // 取出当前区间的左右端点
            ++diff[l];  // 区间起点处覆盖数 +1
            --diff[r + 1];  // 终点后一位 -1；r + 1 最大 51，不会越界
        }  // 结束区间遍历
        int s = 0;  // s 是前缀和，即当前下标被多少个区间覆盖
        for (int i = 0; i < diff.size(); ++i) {  // 遍历所有可能的下标（i 恒非负，与 size() 比较是安全的）
            s += diff[i];  // 累加差分值得到当前位置的覆盖数
            if (s <= 0 && left <= i && i <= right) {  // 覆盖数为 0 且该点落在目标区间内，说明没被完全覆盖
                return false;  // 提前返回 false
            }  // 结束内部判断
        }  // 结束下标遍历
        return true;  // 目标区间内每个点都被覆盖，返回 true
    }  // 方法结束
};  // 类定义结束