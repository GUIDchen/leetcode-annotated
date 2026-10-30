// 题目：3566. 等积子集的划分方案（Partition Array into Two Equal Product Subsets）
// 思路：用二进制位掩码枚举所有子集划分，第 j 位为 1 表示 nums[j] 归入第一组；两组各自累乘，任何一组乘积超过 target 就剪枝，枚举完若两组乘积都等于 target 即返回 true。
// 时间复杂度：O(n * 2^n)，枚举 2^n 种划分、每种最多扫 n 个元素；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkEqualPartitions(vector<int>& nums, long long target) {  // nums：待划分的数组；target：两个子集共同的目标乘积；返回能否把数组分成两组且两组乘积都等于 target
        int n = nums.size();  // 记录数组长度，枚举与内层遍历都依赖它
        for (int i = 0; i < 1 << n; ++i) {  // 枚举全部 2^n 种划分，i 的第 j 位表示 nums[j] 归入哪一组
            long long x = 1, y = 1;  // x、y 分别累乘两组的乘积，初值取乘法单位元 1
            for (int j = 0; j < n; ++j) {  // 逐个元素按当前掩码 i 分配到两组之一
                if ((i >> j & 1) == 1) {  // 取出 i 的第 j 位，为 1 表示 nums[j] 划入第一组
                    x *= nums[j];  // 第一组的乘积乘上该元素
                } else {  // 否则该元素划入第二组
                    y *= nums[j];  // 第二组的乘积乘上该元素
                }  // 元素分配完成，分支结束
                if (x > target || y > target) {  // 剪枝：任一组乘积已超过 target，继续乘只会更大，不可能相等
                    break;  // 提前结束内层循环，换下一种划分
                }  // 剪枝判断结束
            }  // 内层循环结束，得到当前划分下两组的最终乘积
            if (x == target && y == target) {  // 两组乘积都恰好等于 target，说明该划分成立
                return true;  // 找到合法划分，直接返回真
            }  // 判定分支结束
        }  // 外层枚举结束
        return false;  // 所有划分都试过仍不成立，返回假
    }  // 方法结束
};  // 类定义结束