// 题目：2733. 既不是最小值也不是最大值（Neither Minimum nor Maximum）
// 思路：先一次扫描取出数组的最小值与最大值，再扫描一遍，返回第一个既非最小也非最大的元素；全都不满足则返回 -1。
// 时间复杂度：O(n)，只做两次线性扫描；空间复杂度：O(1)，只额外保存两个迭代器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findNonMinOrMax(vector<int>& nums) {  // nums：输入数组；长度不超过 2 时必然不存在这样的元素
        auto [mi, mx] = minmax_element(nums.begin(), nums.end());  // minmax_element 一次遍历同时得到最小值与最大值的迭代器，省掉第二次扫描
        for (int x : nums) {  // 按原顺序遍历，题目只要求返回任意一个符合条件的元素
            if (x != *mi && x != *mx) {  // 解引用得到最小值与最大值本身，判断当前元素是否落在两者之间
                return x;  // 一旦找到就立即返回，无需继续扫描
            }  // if 分支体结束
        }  // for 循环体结束
        return -1;  // 所有元素都等于最小值或最大值（如长度小于 3、或元素全相同），按题意返回 -1
    }  // 方法体结束
};  // 类定义结束