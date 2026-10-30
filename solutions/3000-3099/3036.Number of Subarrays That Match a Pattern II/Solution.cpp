// 题目：3036. 匹配模式数组的子数组数目 II（Number of Subarrays That Match a Pattern II）
// 思路：把 nums 相邻元素的差值就地标准化为 1/0/-1，再用 KMP 在这条关系流上扫描并统计 pattern 的出现次数，整体线性。
// 时间复杂度：O(n + m)，KMP 的失配指针均摊 O(n)；空间复杂度：O(m)，ps 数组存模式串的失配位置。
int ps[1000001];  // KMP 的失配指针（pi）数组，放在全局静态区，避免大数组撑爆函数栈
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {  // nums：原数组；pattern：待统计的关系模式
        int N = size(pattern);  // 模式长度，后面判断「匹配完成」时要用
        ps[0] = -1;  // 失配指针边界：位置 0 失配时回到 -1，表示彻底从头再来
        ps[1] = 0;  // 位置 1 失配时最多退回到位置 0
        for (int i = 2, p = 0; i <= N; ++i) {  // 从第 2 个位置递推 pi；p 是当前最长的相等前后缀长度
            int x = pattern[i - 1];  // 当前待计算位置上的模式字符
            while (p >= 0 && pattern[p] != x) {  // 候选前缀字符与当前字符不相等时不断回退
                p = ps[p];  // 沿失配指针跳到更短的候选前缀
            }
            ps[i] = ++p;  // 匹配成功则长度加一；退到 -1 时 ++p 恰好归零，pi[i] 即为该值
        }

        int res = 0;  // 记录 nums 中与 pattern 匹配的子数组个数
        for (int i = 1, p = 0, M = size(nums); i < M; ++i) {  // 从下标 1 开始扫描相邻差值；p 为当前已匹配长度
            int t = nums[i] - nums[i - 1];  // 当前相邻两个元素的差值
            t = (t > 0) - (t < 0);  // 把差值标准化成 1（上升）/ 0（相等）/ -1（下降）
            while (p >= 0 && pattern[p] != t) {  // 与模式的下一个符号不符时沿失配指针回退
                p = ps[p];  // 退到一个仍然可以继续复用的前缀长度
            }
            if (++p == N) {  // 匹配长度达到模式长度，说明又找到一处完整匹配
                ++res, p = ps[p];  // 计数加一，并回退到可以继续匹配重叠出现的位置
            }
        }
        return res;  // 返回匹配的子数组总数
    }
};
