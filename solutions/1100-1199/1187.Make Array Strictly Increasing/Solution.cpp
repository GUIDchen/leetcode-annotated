// 题目：1187. 使数组严格递增（Make Array Strictly Increasing）
// 思路：排序去重 arr2，在 arr1 两端加 ±inf 哨兵，用 DP 求每个位置「保留原值」时的最少替换数，转移时枚举在 i 前面整段替换的长度 k。
// 时间复杂度：O(n·m + m log m)，m 为 arr2 长度，内层 k 最多到 min(i-1, j)；空间复杂度：O(n + m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {  // arr1 中的元素可以被 arr2 里的值替换，返回使 arr1 严格递增的最少替换次数
        sort(arr2.begin(), arr2.end());  // 先把备选值排序：既方便去重，也方便后面二分
        arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());  // 去掉重复的备选值：同一个数值用一次就够，重复的对答案没有帮助
        const int inf = 1 << 30;  // inf 用来表示「这个状态不可达」，取 1<<30 既足够大又不会溢出
        arr1.insert(arr1.begin(), -inf);  // 头部插入哨兵 -inf：这样「把整个前缀整段替换」也能用统一的状态转移表达
        arr1.push_back(inf);  // 尾部插入哨兵 +inf：它一定比前面任何值都大，答案就落在它身上
        int n = arr1.size();  // 加哨兵后的长度
        vector<int> f(n, inf);  // f[i]：让以 i 结尾的前缀严格递增、且位置 i 保留原值 arr1[i] 时的最少替换数
        f[0] = 0;  // 头哨兵不需要任何替换
        for (int i = 1; i < n; ++i) {  // 按位置依次递推
            if (arr1[i - 1] < arr1[i]) {  // 情况一：前一个位置也保留原值，且两者天然有序
                f[i] = f[i - 1];  // 无需新的替换，直接继承前一个状态
            }  // 分支结束
            // 除了「前一个也保留原值」，还可以把 i 前面连续的 k 个位置整段换掉。
            // 为了让替换块尽量可行，取 arr2 中最大的 k 个小于 arr1[i] 的值，即 arr2[j-k .. j-1]，
            // 于是只需检查替换块前一个保留值是否小于 arr2[j-k]。
            int j = lower_bound(arr2.begin(), arr2.end(), arr1[i]) - arr2.begin();  // j：arr2 中小于 arr1[i] 的元素个数，也就是最多能塞进多少个替换值
            for (int k = 1; k <= min(i - 1, j); ++k) {  // 枚举把 i 前面连续 k 个位置整段替换掉的方案；k 不能超过已有个数，也不能超过可用备选值个数
                if (arr1[i - k - 1] < arr2[j - k]) {  // 替换块前面那个保留值必须小于替换块的最小值，整体才能保持严格递增
                    f[i] = min(f[i], f[i - k - 1] + k);  // 代价 = 前面位置的代价 + 本段替换的 k 个值
                }  // 内层循环结束
            }  // k 枚举结束
        }  // 所有状态计算完毕
        return f[n - 1] >= inf ? -1 : f[n - 1];  // 尾哨兵仍不可达说明怎么替换都做不到，返回 -1
    }  // 方法结束
};  // 类定义结束