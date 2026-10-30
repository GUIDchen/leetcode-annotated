// 题目：27. 移除元素（Remove Element）
// 思路：快慢双指针原地覆盖。慢指针 k 指向下一个可写位置，快指针 x 顺序扫描；只要当前元素不等于 val 就把它保留到 k 位置。等于 val 的元素被后面的元素自然覆盖掉。
// 时间复杂度：O(n)，一趟扫描；空间复杂度：O(1)，只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int removeElement(vector<int>& nums, int val) {  // nums：待处理数组；val：要删除的值；返回删除后剩下的元素个数
        int k = 0;  // k 记录已保留的元素个数，也是下一个待写入的位置
        for (int x : nums) {  // 用范围 for 顺序读取每个元素；k 不超过当前下标，覆盖写是安全的
            if (x != val) {  // 当前元素不是要删除的值，需要保留
                nums[k++] = x;  // 写到前 k 个位置之后，再把 k 加一；后置 ++ 先使用旧值
            }
        }
        return k;  // 前 k 个位置就是保留的元素，返回其个数
    }
};
