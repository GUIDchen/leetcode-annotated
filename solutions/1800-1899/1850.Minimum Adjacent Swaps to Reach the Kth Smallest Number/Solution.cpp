// 题目：1850. 邻位交换的最小次数（Minimum Adjacent Swaps to Reach the Kth Smallest Number）
// 思路：先求 num 的第 k 个下一个排列得到目标串，再把目标串的每位映射回原串下标，逆序对数即最少相邻交换次数。
// 时间复杂度：O(k·n + n^2)，求排列 O(k·n)、统计逆序对 O(n^2)；空间复杂度：O(n)，要存映射数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getMinSwaps(string num, int k) {  // num：数字字符串；k：要到达的是第 k 个更大的最小数
        string s = num;  // 复制一份，准备在副本上反复求下一个排列
        for (int i = 0; i < k; ++i) {  // 连续求 k 次下一个排列，得到第 k 个最小数
            next_permutation(begin(s), end(num));  // 把 s 推进到下一个更大的排列（end(num) 与 end(s) 等价，两者等长）
        }  // 结束 for
        vector<int> d[10];  // 10 个桶，按数字 0~9 分别记录它在原串中出现的位置
        int n = num.size();  // 字符串长度
        for (int i = 0; i < n; ++i) {  // 统计原串中每个数字的所有下标
            d[num[i] - '0'].push_back(i);  // 记录数字 num[i] 出现的位置
        }  // 结束 for
        int idx[10]{};  // 每个数字下一个待配对的位置指针，按出现顺序贪心配对
        vector<int> arr(n);  // arr[i] 表示目标串第 i 位应当由原串哪个下标移动过来
        for (int i = 0; i < n; ++i) {  // 逐位建立目标串到原串下标的映射
            arr[i] = d[s[i] - '0'][idx[s[i] - '0']++];  // 同一种数字按下标从小到大依次配对，得到它在原串中的位置
        }  // 结束 for
        int ans = 0;  // 相邻交换的最少次数等于映射数组的逆序对数
        for (int i = 0; i < n; ++i) {  // 枚举每一对位置
            for (int j = 0; j < i; ++j) {  // 只考察排在 i 之前的 j
                if (arr[j] > arr[i]) {  // 前面的下标反而更大，说明这一对的相对顺序反了
                    ++ans;  // 计数一个逆序对
                }  // 结束 if
            }  // 结束内层 for
        }  // 结束外层 for
        return ans;  // 返回逆序对数
    }  // 结束 getMinSwaps
};  // 结束 Solution 类