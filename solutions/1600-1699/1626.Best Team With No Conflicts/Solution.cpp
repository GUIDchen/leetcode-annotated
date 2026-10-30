// 题目：1626. 无矛盾的最佳球队（Best Team With No Conflicts）
// 思路：把「分数, 年龄」按分数升序排序，问题化为在年龄非降的前提下选子序列使分数和最大，用 O(n²) 的 DP 求解。
// 时间复杂度：O(n²)，排序 O(n log n) 之外还有两层循环；空间复杂度：O(n)，存放二元组与 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {  // scores 为球员分数，ages 为球员年龄，返回无矛盾球队的最大总分
        int n = ages.size();  // 球员人数
        vector<pair<int, int>> arr(n);  // 把「分数, 年龄」二元组放进数组，方便统一排序
        for (int i = 0; i < n; ++i) {  // 逐个读入球员
            arr[i] = {scores[i], ages[i]};  // 先放分数、后放年龄，这样 sort 默认先按分数升序、分数相同再按年龄升序
        }  // 读入循环结束
        sort(arr.begin(), arr.end());  // 排序后按分数从小到大处理，选人时只需保证年龄不降
        vector<int> f(n);  // f[i]：以第 i 个球员作为球队最后一名时能取得的最大总分
        for (int i = 0; i < n; ++i) {  // 依次考虑每个球员作为队尾
            for (int j = 0; j < i; ++j) {  // 枚举它可以接在前面的哪个球员 j 之后
                if (arr[i].second >= arr[j].second) {  // 年龄不小于前一名球员时，两人之间才不会产生矛盾
                    f[i] = max(f[i], f[j]);  // 从更优的前驱状态转移过来
                }  // if 分支结束
            }  // 内层循环结束
            f[i] += arr[i].first;  // 把当前球员的分数加入以他结尾的球队总分
        }  // 外层循环结束
        return *max_element(f.begin(), f.end());  // 所有可能的队尾里取最大值即为答案
    }  // 方法结束
};  // 类定义结束