// 题目：1191. K 次串联后最大子数组之和（K-Concatenation Maximum Sum）
// 思路：先求单段的最大子数组和、最大前缀和、最大后缀和；k>1 时答案还能是「首段前缀 + 中间整段 + 末段后缀」，总和为正时中间整段全部计入。
// 时间复杂度：O(n)，只需扫一遍原数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int kConcatenationMaxSum(vector<int>& arr, int k) {  // arr：原数组，k：重复次数；返回重复 k 次后的最大子数组和（对 1e9+7 取模）
        long s = 0, mxPre = 0, miPre = 0, mxSub = 0;  // s 前缀和；mxPre/miPre 前缀和的最大/最小值；mxSub 单段内的最大子数组和
        for (int x : arr) {  // 扫一遍原数组即可拿到所有需要的信息
            s += x;  // 累加前缀和
            mxPre = max(mxPre, s);  // 更新最大前缀和（对应「最优答案从最左端开始」的情况）
            miPre = min(miPre, s);  // 更新最小前缀和（用于算后缀和）
            mxSub = max(mxSub, s - miPre);  // 当前前缀和减去历史最小前缀和，就是以此处结尾的最大子数组和
        }  // 扫描结束
        long ans = mxSub;  // k == 1 时答案只能是单段的最大子数组和
        const int mod = 1e9 + 7;  // 题目要求的模数
        if (k == 1) {  // 只有一段，没有跨段拼接的可能
            return ans % mod;  // 直接取模返回
        }  // 分支结束
        long mxSuf = s - miPre;  // 最大后缀和 = 总和 - 最小前缀和
        ans = max(ans, mxPre + mxSuf);  // 跨两段拼接：第一段的最大前缀 + 第二段的最大后缀
        if (s > 0) {  // 总和为正时，中间多夹的整段都应该算进来
            ans = max(ans, mxPre + (k - 2) * s + mxSuf);  // 首段最大前缀 + 中间 (k-2) 个完整 arr 的总和 + 末段最大后缀
        }  // 分支结束
        return ans % mod;  // 取模后返回最终答案
    }  // 方法结束
};  // 类定义结束