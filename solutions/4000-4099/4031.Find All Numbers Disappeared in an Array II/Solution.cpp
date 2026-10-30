// 4031. 找到所有数组中消失的数字 II / Find All Numbers Disappeared in an Array II
// 核心思路：排序后顺序扫描落在 [lower, upper] 内的数字，相邻两个已出现数字之间的空缺就是消失的区间，最后再补上尾部区间。
// 复杂度：时间 O(n log n)，空间 O(1) 额外（不计排序与结果）。
class Solution {  // 题解类定义
public:  // 公有成员：判题器调用的接口
    vector<vector<int>> findDisappearedNumbers(vector<int>& nums, int lower, int upper) {  // 返回 [lower, upper] 中未出现在 nums 里的所有数字区间
        sort(nums.begin(), nums.end());  // 先排序，便于顺序扫描并合并区间
        vector<vector<int>> ans;  // 保存结果区间
        int prev = lower - 1;  // 上一个出现过的数字，从 lower - 1 开始
        for (int x : nums) {  // 顺序扫描排序后的每个数字
            if (x < lower || x > upper) {  // 落在区间外的数字对答案没有影响
                continue;  // 直接跳过
            }  // 结束区间过滤
            if (x - prev > 1) {  // 相邻两个已出现数字之间存在空缺
                ans.push_back({prev + 1, x - 1});  // 把空缺区间 [prev + 1, x - 1] 加入答案
            }  // 结束空缺判断
            prev = x;  // 更新上一个出现过的数字
        }  // 结束扫描
        if (prev < upper) {  // 尾部还有未覆盖的数字
            ans.push_back({prev + 1, upper});  // 补上尾部区间 [prev + 1, upper]
        }  // 结束尾部处理
        return ans;  // 返回所有消失的数字区间
    }  // 结束函数
};  // 结束类定义
