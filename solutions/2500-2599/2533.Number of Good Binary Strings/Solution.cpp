// 题目：2533. 好二进制字符串的数量（Number of Good Binary Strings）
// 核心思路：线性 DP。f[i] 表示长度为 i 的好串数目；好串去掉末尾一段连续的 1（长 oneGroup）或一段连续的 0（长 zeroGroup）仍是好串，故 f[i] = f[i - oneGroup] + f[i - zeroGroup]，最后对长度落在 [minLength, maxLength] 的 f 求和。
// 时间复杂度：O(maxLength)，一趟递推加一趟求和；空间复杂度：O(maxLength)，一维 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int goodBinaryStrings(int minLength, int maxLength, int oneGroup, int zeroGroup) {  // minLength / maxLength 为长度区间，oneGroup / zeroGroup 分别是「1 组」与「0 组」的固定块长度
        const int mod = 1e9 + 7;  // 结果要对 1e9+7 取模，防止计数溢出
        int f[maxLength + 1];  // f[i]：长度为 i 的好二进制串个数（变长数组，长度由参数决定）
        memset(f, 0, sizeof f);  // 整块清零，保证未赋值的状态都是 0
        f[0] = 1;  // 长度为 0 的空串作为递推的合法起点，计数为 1
        for (int i = 1; i <= maxLength; ++i) {  // 按长度从小到大递推每个状态
            if (i - oneGroup >= 0) {  // 长度足够放下一整组 1
                f[i] = (f[i] + f[i - oneGroup]) % mod;  // 末尾接 oneGroup 个 1，方案数来自长度 i-oneGroup
            }  // 放不下一组 1 就跳过这个转移
            if (i - zeroGroup >= 0) {  // 长度足够放下一整组 0
                f[i] = (f[i] + f[i - zeroGroup]) % mod;  // 末尾接 zeroGroup 个 0，方案数来自长度 i-zeroGroup
            }  // 放不下一组 0 就跳过这个转移
        }  // 所有长度的状态都计算完毕
        int ans = 0;  // 累计落在合法长度区间内的方案数
        for (int i = minLength; i <= maxLength; ++i) {  // 枚举长度区间 [minLength, maxLength]
            ans = (ans + f[i]) % mod;  // 把该长度的好串数目累加进答案并取模
        }  // 区间求和结束
        return ans;  // 返回区间内好串的总数
    }  // 方法结束
};  // 类定义结束