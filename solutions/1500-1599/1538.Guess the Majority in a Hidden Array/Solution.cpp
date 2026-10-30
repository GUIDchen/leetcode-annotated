// 题目：1538. 找出隐藏数组中出现次数最多的元素（Guess the Majority in a Hidden Array）
// 思路：以 query(0,1,2,3) 为基准，把下标 4 起的元素按「是否与下标 3 同值」分成两组，再用元素 4 把下标 0/1/2 也分进这两组，人数多的一组就是多数派。
// 时间复杂度：O(n)，query 至多调用 O(n) 次；空间复杂度：O(1)，只用常数个计数变量。
/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares 4 different elements in the array
 *     // return 4 if the values of the 4 elements are the same (0 or 1).
 *     // return 2 if three elements have a value equal to 0 and one element has value equal to 1 or vice versa.
 *     // return 0 : if two element have a value equal to 0 and two elements have a value equal to 1.
 *     int query(int a, int b, int c, int d);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int guessMajority(ArrayReader& reader) {  // reader：隐藏数组的交互接口，只能通过 query 与 length 访问
        int n = reader.length();  // n：隐藏数组的长度
        int x = reader.query(0, 1, 2, 3);  // 基准值 x：查询前 4 个元素，作为后续「同值/不同值」判断的参照
        int a = 1, b = 0;  // a 统计与下标 3 同值的元素个数（初值 1 代表下标 3 自己）；b 统计与下标 3 不同值的个数
        int k = 0;  // k 记下「不同值」那一组的任意一个下标，最后用它作为答案
        for (int i = 4; i < n; ++i) {  // 从下标 4 开始逐个把查询里的第 4 个位置换成 i
            if (reader.query(0, 1, 2, i) == x) {  // 结果与基准相同，说明 a[i] 与 a[3] 同值
                ++a;  // 同值个数加 1
            } else {  // 否则 a[i] 与 a[3] 不同值
                ++b;  // 不同值个数加 1
                k = i;  // 顺手记下这一组的代表下标
            }
        }  // 结束对下标 4 及之后元素的划分

        int y = reader.query(0, 1, 2, 4);  // 换一个基准 y：把查询 (0,1,2,3) 的第 4 个位置换成 4
        if (reader.query(1, 2, 3, 4) == y) {  // 与 y 相同说明 a[0] 与 a[3] 同值，归入 a 组
            ++a;  // 同值个数加 1
        } else {  // 不同说明 a[0] 属于另一组
            ++b;  // 不同值个数加 1
            k = 0;  // 另一组的代表下标是 0
        }
        if (reader.query(0, 2, 3, 4) == y) {  // 同理判定下标 1：与 y 相同即与 a[3] 同值
            ++a;  // 同值个数加 1
        } else {  // 属于另一组
            ++b;  // 不同值个数加 1
            k = 1;  // 另一组的代表下标是 1
        }
        if (reader.query(0, 1, 3, 4) == y) {  // 同理判定下标 2：与 y 相同即与 a[3] 同值
            ++a;  // 同值个数加 1
        } else {  // 属于另一组
            ++b;  // 不同值个数加 1
            k = 2;  // 另一组的代表下标是 2
        }
        if (a == b) {  // 两组元素一样多，说明不存在严格多数派
            return -1;  // 按题意返回 -1
        }
        return a > b ? 3 : k;  // 与 a[3] 同值的元素更多就返回下标 3，否则返回另一组的代表下标 k
    }
};