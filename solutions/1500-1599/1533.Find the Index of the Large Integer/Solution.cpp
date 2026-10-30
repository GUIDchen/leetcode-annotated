// 题目：1533. 找到最大整数的索引（Find the Index of the Large Integer）
// 思路：数组除一个最大元素外其余全相等，于是把区间三分，比较前两段的和即可确定最大值落在哪一段，逐步缩小区间。
// 时间复杂度：O(log n)，每次区间缩为约 1/3；空间复杂度：O(1)，只用了几个下标变量。
/**  // 下面这段是题面给出的 ArrayReader 接口说明，无需自己实现
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares the sum of arr[l..r] with the sum of arr[x..y]
 *     // return 1 if sum(arr[l..r]) > sum(arr[x..y])
 *     // return 0 if sum(arr[l..r]) == sum(arr[x..y])
 *     // return -1 if sum(arr[l..r]) < sum(arr[x..y])
 *     int compareSub(int l, int r, int x, int y);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getIndex(ArrayReader& reader) {  // reader：题目提供的接口，只能调用 compareSub 和 length
        int left = 0, right = reader.length() - 1;  // 答案一定在当前区间 [left, right] 中，初始为整个数组
        while (left < right) {  // 区间还没缩到单点就继续三分
            int t1 = left, t2 = left + (right - left) / 3, t3 = left + (right - left) / 3 * 2 + 1;  // 把区间均分成 A=[t1,t2]、B=[t2+1,t3]，剩下的 [t3+1,right] 为 C 段
            int cmp = reader.compareSub(t1, t2, t2 + 1, t3);  // 比较 A、B 两段元素之和
            if (cmp == 0) {  // 两段和相等，说明最大值不在 A、B 中，只可能在还没比的 C 段
                left = t3 + 1;  // 把查找区间收缩到 C 段
            } else if (cmp == 1) {  // A 段和更大，说明最大值落在 A 段
                right = t2;  // 右边界收到 A 段末尾
            } else {  // 否则是 B 段和更大，最大值落在 B 段
                left = t2 + 1;  // 左边界移到 B 段开头
                right = t3;  // 右边界移到 B 段末尾
            }  // if/else 分支结束
        }  // while 循环结束
        return left;  // 区间缩成单点，left 就是最大整数的下标
    }  // getIndex 方法结束
};  // 题解类结束