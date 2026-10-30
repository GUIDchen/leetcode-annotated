// 题目：1095. 山脉数组中查找目标值（Find in Mountain Array）
// 思路：先二分出山脉峰值，再用「乘以 k 统一翻转」的技巧在左侧升序段与右侧降序段各做一次二分。
// 时间复杂度：O(log n)，两次二分都是对数级；空间复杂度：O(1)，只用了常数个下标变量。
// 题目给定的 MountainArray 接口说明：实现由判题器提供，这里只按接口调用，不要自己实现。
/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findInMountainArray(int target, MountainArray& mountainArr) {  // target：要找的值；mountainArr：只允许通过 get / length 访问的山脉数组
        int n = mountainArr.length();  // 数组长度
        int l = 0, r = n - 1;  // 二分区间 [l, r] 初始为整个数组
        while (l < r) {  // 第一次二分：定位峰值（山顶）下标
            int mid = (l + r) >> 1;  // 取中点，(l + r) >> 1 就是向下取整的 (l + r) / 2
            if (mountainArr.get(mid) > mountainArr.get(mid + 1)) {  // mid 右侧开始下降，说明峰值在 mid 或 mid 左侧
                r = mid;  // 峰值上界收缩到 mid
            } else {  // 否则还在爬升，峰值在 mid 右侧
                l = mid + 1;  // 峰值下界跳到 mid + 1，mid 本身被排除
            }  // if / else 结束
        }  // 循环结束时 l == r，即峰值下标
        auto search = [&](int l, int r, int k) -> int {  // 通用二分 lambda：k = 1 查左侧升序段，k = -1 查右侧降序段
            while (l < r) {  // 在当前区间 [l, r] 上二分
                int mid = (l + r) >> 1;  // 取中点
                if (k * mountainArr.get(mid) >= k * target) {  // 乘以 k 把降序段镜像成升序；>= target 说明答案落在左半 [l, mid]
                    r = mid;  // 收缩右边界
                } else {  // 否则答案严格在右半部分
                    l = mid + 1;  // 排除 mid，收缩左边界
                }  // else 分支结束
            }  // while 结束
            return mountainArr.get(l) == target ? l : -1;  // 循环结束时 l 是第一个满足条件的位置；值等于 target 才返回下标，否则 -1
        };  // lambda 定义结束
        int ans = search(0, l, 1);  // 先在整个升序段（含峰值）里找，题目要求返回最小下标
        return ans == -1 ? search(l + 1, n - 1, -1) : ans;  // 左侧找不到才去降序段（峰值右侧）找；都没有则返回 -1
    }  // 方法结束
};  // 类定义结束