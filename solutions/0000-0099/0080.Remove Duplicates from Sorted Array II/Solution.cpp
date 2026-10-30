// 题目：80. 删除有序数组中的重复项 II（Remove Duplicates from Sorted Array II）
// 思路：快慢指针（读写指针）。k 是已写好的长度，nums[k-2] 是保留下来的倒数第二个元素；只要新元素与它不同，就说明同一个值最多已保留 2 个，可以继续写入。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用一个写指针，原地修改。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int removeDuplicates(vector<int>& nums) {  // nums 是非递减数组，要求原地去重使每个值最多出现两次，并返回新长度
        int k = 0;  // k 是写指针，同时也表示已经保留的元素个数
        for (int x : nums) {  // 读指针 x 依次扫过每个元素
            if (k < 2 || x != nums[k - 2]) {  // 前两个元素直接保留；否则只有与已保留的倒数第二个元素不同才允许写入
                nums[k++] = x;  // 把 x 写到 k 位置并让 k 后移，完成一次原地保留
            }
        }
        return k;  // 返回保留后的有效长度
    }
};