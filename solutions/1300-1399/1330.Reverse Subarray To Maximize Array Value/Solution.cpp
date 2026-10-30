// 题目：1330. 翻转子数组得到最大的数组值（Reverse Subarray To Maximize Array Value）
// 思路：先算出原数组值 s；翻转贴着左端或右端时只改一条边，直接枚举；翻转区间在中间时用 4 种符号组合把绝对值展开成线性式，用 max(a-b) - min(a+b) 求最大净增益。
// 时间复杂度：O(n)，常数倍线性扫描；空间复杂度：O(1)，只用若干标量。
class Solution {  // 题解类
public:  // 对外暴露题解接口
    int maxValueAfterReverse(vector<int>& nums) {  // nums：输入数组，返回翻转一次子数组后可能得到的最大数组值
        int n = nums.size();  // 元素个数
        int s = 0;  // s 保存不翻转时的数组值，即所有相邻差的绝对值之和
        for (int i = 0; i < n - 1; ++i) {  // 相邻对只有 n-1 个
            s += abs(nums[i] - nums[i + 1]);  // 累加 |nums[i] - nums[i+1]|
        }  // 求 s 结束
        int ans = s;  // 答案下界：不翻转（或翻转单元素）时的数组值
        for (int i = 0; i < n - 1; ++i) {  // 枚举每条边，处理翻转区间贴着一端的情况
            ans = max(ans, s + abs(nums[0] - nums[i + 1]) - abs(nums[i] - nums[i + 1]));  // 翻转前缀 [0, i]：边 (nums[i], nums[i+1]) 变成 (nums[0], nums[i+1])，其余边不变
            ans = max(ans, s + abs(nums[n - 1] - nums[i]) - abs(nums[i] - nums[i + 1]));  // 翻转后缀 [i+1, n-1]：这条边变成 (nums[i], nums[n-1])
        }  // 贴着两端的枚举结束
        int dirs[5] = {1, -1, -1, 1, 1};  // 方案二：把 |x-y| 按符号展开时只有 4 种系数组合，dirs 相邻两项就是一组 (k1, k2)
        const int inf = 1 << 30;  // inf 作为足够大的「无穷」，避免溢出（1<<30 仍远小于 int 上限）
        for (int k = 0; k < 4; ++k) {  // 遍历 4 种符号组合
            int k1 = dirs[k], k2 = dirs[k + 1];  // 取出当前组合的两个符号系数
            int mx = -inf, mi = inf;  // mx 维护 a-b 的最大值，mi 维护 a+b 的最小值，二者之差即中间翻转的增益上界
            for (int i = 0; i < n - 1; ++i) {  // 遍历所有相邻对
                int a = k1 * nums[i] + k2 * nums[i + 1];  // 去掉绝对值后的线性组合 k1*x + k2*y
                int b = abs(nums[i] - nums[i + 1]);  // 原来这条边的贡献 |x - y|
                mx = max(mx, a - b);  // 记录 a - b 的最大值
                mi = min(mi, a + b);  // 记录 a + b 的最小值
            }  // 内层遍历结束
            ans = max(ans, s + max(0, mx - mi));  // 中间翻转的净增益为 mx-mi，小于 0 说明不如不翻，故与 0 取 max
        }  // 4 种组合枚举结束
        return ans;  // 返回最大数组值
    }  // 方法结束
};  // 类定义结束