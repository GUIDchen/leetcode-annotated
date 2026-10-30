// 题目：2495. 乘积为偶数的子数组数（Number of Subarrays Having Even Product）
// 思路：子数组乘积为偶数 等价于 子数组里至少有一个偶数；枚举右端点，只需知道最近的偶数下标 last，左端点取 0..last 即可。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long evenProduct(vector<int>& nums) {  // nums 是输入数组，返回乘积为偶数的子数组个数
        long long ans = 0;  // 答案用 long long：子数组总数可达 O(n^2)，int 会溢出
        int last = -1;  // 记录最近一次出现的偶数下标，-1 表示还没遇到过偶数
        for (int i = 0; i < nums.size(); ++i) {  // 枚举子数组的右端点 i
            if (nums[i] % 2 == 0) {  // 当前元素是偶数
                last = i;  // 更新最近偶数的位置，它右边的左端点都能把这个偶数包进来
            }
            ans += last + 1;  // 左端点取 0..last 共 last+1 个，区间必含偶数，乘积必为偶数
        }
        return ans;  // 返回乘积为偶数的子数组总数
    }
};  // 类定义结束