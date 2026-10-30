// 3779. 得到互不相同元素的最少操作次数 / Minimum Number of Operations to Have Distinct Elements
// 核心思路：每次操作删除末尾三个元素，所以从后往前扫描并记录出现过的值，第一次遇到重复值的位置 i 决定必须删到哪一组之后，返回 i/3+1。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为数组长度。
class Solution {  // 定义题解类
public:  // 公有成员
    int minOperations(vector<int>& nums) {  // 返回使剩余前缀元素互不相同的最少操作次数
        unordered_set<int> st;  // 记录从后往前已经出现过的不同元素
        for (int i = nums.size() - 1; ~i; --i) {  // 从后往前扫描，模拟每次删掉末尾三个元素
            if (st.contains(nums[i])) {  // 该元素在前缀中重复出现
                return i / 3 + 1;  // 必须删掉它所在的整组以及之后的元素
            }  // 分支结束
            st.insert(nums[i]);  // 记录该元素已经出现
        }  // 扫描结束
        return 0;  // 没有重复元素，无需任何操作
    }  // 方法结束
};  // 类定义结束
