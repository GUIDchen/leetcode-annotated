// 3397. 执行操作后不同元素的最大数量 / Maximum Number of Distinct Elements After Operations
// 核心思路：先排序，再贪心地从小到大为每个元素挑选可取值区间 [x-k, x+k] 内大于上一个已占用值的最小值，能取到就贡献一个不同元素
// 复杂度：时间 O(n log n)（排序主导）、空间 O(1)（不计排序开销）
class Solution {  // 定义 Solution 类
public:  // 公有方法
    int maxDistinctElements(vector<int>& nums, int k) {  // 求执行操作后不同元素的最大数量
        ranges::sort(nums);  // 先对数组升序排序，便于从左到右贪心分配
        int ans = 0, pre = INT_MIN;  // ans 记录不同元素个数，pre 记录上一个已被占用的值
        for (int x : nums) {  // 按从小到大依次处理每个元素
            int cur = min(x + k, max(x - k, pre + 1));  // 当前元素可取值区间为 [x-k, x+k]，贪心地取大于 pre 的最小值
            if (cur > pre) {  // 取到的值大于 pre，说明可以新增一个不同元素
                ++ans;  // 不同元素个数加一
                pre = cur;  // 更新已被占用的最大值
            }  // 判断结束
        }  // 循环结束
        return ans;  // 返回答案
    }  // 方法结束
};  // 类定义结束
