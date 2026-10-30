// 题目：2161. 根据给定数字划分数组（Partition Array According to Given Pivot）
// 核心思路：按「小于 pivot、等于 pivot、大于 pivot」三遍扫描原数组，依次把元素追加到答案中，天然保持各自的原相对顺序。
// 时间复杂度：O(n)，数组只被完整扫描三遍；空间复杂度：O(n)，答案数组与原数组等长。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> pivotArray(vector<int>& nums, int pivot) {  // nums：输入数组；pivot：划分基准值
        vector<int> ans;  // 结果数组，按「小于、等于、大于」的顺序收集元素
        for (int& x : nums) {  // 第一遍：收集所有严格小于 pivot 的元素
            if (x < pivot) {  // 只挑严格小于 pivot 的
                ans.push_back(x);  // 按原顺序放入结果，保持相对次序
            }  // 小于分支结束
        }  // 第一遍扫描结束
        for (int& x : nums) {  // 第二遍：收集所有等于 pivot 的元素
            if (x == pivot) {  // 只挑等于 pivot 的
                ans.push_back(x);  // 按原顺序放入结果
            }  // 等于分支结束
        }  // 第二遍扫描结束
        for (int& x : nums) {  // 第三遍：收集所有严格大于 pivot 的元素
            if (x > pivot) {  // 只挑严格大于 pivot 的
                ans.push_back(x);  // 按原顺序放入结果
            }  // 大于分支结束
        }  // 第三遍扫描结束
        return ans;  // 返回划分后的数组
    }  // 方法结束
};  // 题解类定义结束
