// 题目：3932. 统计区间内的完全 K 次幂数量（Count K-th Roots in a Range）
// 思路：k = 1 时区间内每个整数都是 1 次幂，直接返回区间长度；否则从小到大枚举底数 x，累乘 k 次得到 y，一旦 y > r 就停止枚举，落在 [l, r] 内则计数。
// 时间复杂度：O(r^(1/k) · k)，底数只枚举到 r 的 k 次方根附近；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countKthRoots(int l, int r, int k) {  // l、r：闭区间端点；k：幂次，返回完全 k 次幂的个数
        if (k == 1) {  // 一次幂需要特判
            return r - l + 1;  // 区间内每个整数都是完全 1 次幂
        }  // 特判结束
        int ans = 0;  // 完全 k 次幂的个数
        for (int x = 0;; x++) {  // 底数从 0 开始无限枚举，靠 y > r 跳出
            long long y = 1;  // 用 long long 累乘，避免中途溢出
            for (int i = 0; i < k; i++) {  // 计算 x 的 k 次幂
                y *= x;  // 逐次累乘
                if (y > r) {  // 已经超过上界
                    break;  // 提前结束幂计算，后面只会更大
                }  // 溢出判断结束
            }  // 幂计算结束
            if (y > r) {  // 底数 x 的 k 次幂已经超过 r
                break;  // 更大的底数同样超界，枚举结束
            }  // 跳出判断结束
            if (l <= y && y <= r) {  // y 落在闭区间内
                ans++;  // 计数加一
            }  // 区间判断结束
        }  // 枚举结束
        return ans;  // 返回个数
    }  // 方法结束
};  // 类定义结束