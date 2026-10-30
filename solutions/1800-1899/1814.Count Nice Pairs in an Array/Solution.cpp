// 题目：1814. 统计一个数组中好对子的数目（Count Nice Pairs in an Array）
// 思路：好对子条件 nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])，移项得 nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])，于是统计每种差值的出现次数并两两组合。
// 时间复杂度：O(n * log10(maxVal))，每个数反转一次再统计一次；空间复杂度：O(n)，哈希表最多存 n 个不同的差值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countNicePairs(vector<int>& nums) {  // nums：输入数组
        auto rev = [](int x) {  // 定义局部 lambda：把整数按十进制位反转
            int y = 0;  // y 累积反转后的结果
            for (; x > 0; x /= 10) {  // 每轮取走最低位，直到 x 变为 0
                y = y * 10 + x % 10;  // 把 x 的最低位接到 y 的末尾
            }
            return y;  // 返回反转后的整数
        };  // lambda 定义结束
        unordered_map<int, int> cnt;  // 哈希表：键是 nums[i] - rev(nums[i])，值是出现次数
        for (int& x : nums) {  // 遍历数组中的每个元素（引用遍历，避免拷贝）
            int y = x - rev(x);  // 计算该元素的“好对子特征值”
            cnt[y]++;  // 特征值相同即可配对，累加该特征值的计数
        }
        long long ans = 0;  // 答案用 long long 防止组合数累加时溢出 int
        const int mod = 1e9 + 7;  // 题目要求的取模值
        for (auto& [_, v] : cnt) {  // 结构化解包遍历哈希表：_ 是特征值（不使用），v 是该特征值的出现次数
            ans = (ans + 1ll * v * (v - 1) / 2) % mod;  // 从 v 个元素中任选 2 个的组合数 C(v,2)，边加边取模
        }
        return ans;  // 返回好对子的总数
    }
};  // 结束 Solution 类定义