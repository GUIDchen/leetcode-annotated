// 题目：1387. 将整数按权重排序（Sort Integers by The Power Value）
// 思路：按题意模拟 3x+1 过程算出每个数的权重，再用自定义比较器按「权重升序、数值升序」排序取第 k 个。
// 时间复杂度：O(n log n + n log V)，排序加每次迭代求权重；空间复杂度：O(n)，存放区间内的所有整数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getKth(int lo, int hi, int k) {  // lo..hi 是取值区间，k 是名次
        auto f = [](int x) {  // 匿名函数：计算 x 的权重（变换到 1 所需的步数）
            int ans = 0;  // 步数计数器
            for (; x != 1; ++ans) {  // 每轮先把 x 变一次，循环末尾再累加步数
                if (x % 2 == 0) {  // x 是偶数
                    x /= 2;  // 折半
                } else {  // x 是奇数
                    x = 3 * x + 1;  // 按 3x+1 规则变换
                }  // 奇偶分支结束
            }  // 变换到 1，循环结束
            return ans;  // 返回总步数
        };  // 匿名函数结束
        vector<int> nums;  // 存放 [lo, hi] 区间内的全部整数
        for (int i = lo; i <= hi; ++i) {  // 逐个生成区间内的数
            nums.push_back(i);  // 追加到数组
        }  // 生成结束
        sort(nums.begin(), nums.end(), [&](int x, int y) {  // 捕获 f 的自定义排序规则
            int fx = f(x), fy = f(y);  // 分别计算两个数的权重
            if (fx != fy) {  // 权重不相同
                return fx < fy;  // 权重小的排在前面
            } else {  // 权重相同
                return x < y;  // 数值小的排在前面
            }  // 比较规则结束
        });  // 排序结束
        return nums[k - 1];  // 第 k 小对应下标 k-1
    }  // getKth 结束
};  // Solution 类结束