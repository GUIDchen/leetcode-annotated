// 题目：1389. 按既定顺序创建目标数组（Create Target Array in the Given Order）
// 思路：按 nums 的下标顺序逐个处理，把 nums[i] 插入 target 的第 index[i] 个位置，插入时后面的元素会自动右移。
// 时间复杂度：O(n^2)，每次 vector 插入平均要移动 O(n) 个元素；空间复杂度：O(n)，target 存放 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {  // nums：待插入的数值；index：每个数值对应的插入位置
        vector<int> target;  // 目标数组，初始为空
        for (int i = 0; i < nums.size(); ++i) {  // 按下标顺序依次处理第 i 个元素
            target.insert(target.begin() + index[i], nums[i]);  // 把 nums[i] 插到 target 的第 index[i] 个位置，原有元素整体右移一位
        }  // 循环结束：所有元素都已按规则插入完毕
        return target;  // 返回构造完成的目标数组
    }
};