// 题目：2136. 全部开花的最早一天（Earliest Possible Day of Full Bloom）
// 思路：播种必须串行，所以总播种时间固定；把生长期长的种子尽量往前排（按 growTime 降序），用贪心交换论证可证最优，逐颗累加播种时间并取 t + growTime[i] 的最大值。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，存放下标数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {  // plantTime：各种子的播种耗时；growTime：各种子的生长期
        int n = plantTime.size();  // n 是种子个数
        vector<int> idx(n);  // idx 存放种子下标，用来按生长期排序
        iota(idx.begin(), idx.end(), 0);  // 从 0 开始依次填充 0..n-1
        sort(idx.begin(), idx.end(), [&](int i, int j) { return growTime[j] < growTime[i]; });  // 按生长期从大到小排序：生长期长的种子先播种
        int ans = 0, t = 0;  // ans：全部开花的最早一天；t：当前已累计的播种时间
        for (int i : idx) {  // 按生长期降序依次播种
            t += plantTime[i];  // 累计播种耗时，该种子在时刻 t 播完
            ans = max(ans, t + growTime[i]);  // 该种子在 t + growTime[i] 开花，用最大值更新答案
        }  // 全部种子播种结束
        return ans;  // 返回全部开花的最早一天
    }  // earliestFullBloom 方法结束
};  // Solution 类结束