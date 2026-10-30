// 题目：1618. 找出适应屏幕的最大字号（Maximum Font to Fit a Sentence in a Screen）
// 思路：字号是否放得下具有单调性（字号越大越放不下），因此在有序的 fonts 上二分，用上取整中点逼近最后一个可行下标。
// 时间复杂度：O(k log m)，k 为句子长度、m 为可选字号数；空间复杂度：O(1)，只用常数个变量。
/**
 * // This is the FontInfo's API interface.
 * // You should not implement it, or speculate about its implementation
 * class FontInfo {
 *   public:
 *     // Return the width of char ch when fontSize is used.
 *     int getWidth(int fontSize, char ch);
 *
 *     // Return Height of any char when fontSize is used.
 *     int getHeight(int fontSize)
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxFont(string text, int w, int h, vector<int>& fonts, FontInfo fontInfo) {  // text：句子；w/h：宽高限制；fonts：递增的可选字号；fontInfo：判题器提供的度量接口
        auto check = [&](int size) {  // 判断字号 size 能否把整句放进屏幕
            if (fontInfo.getHeight(size) > h) return false;  // 高度超标直接判负，省去后面的宽度累加
            int width = 0;  // 累计这一行句子的总宽度
            for (char& c : text) {  // 逐字符查表累加宽度
                width += fontInfo.getWidth(size, c);  // 该字符在 size 字号下的宽度
            }
            return width <= w;  // 总宽度不超过屏幕宽度才算放得下
        };
        int left = 0, right = fonts.size() - 1;  // 二分的闭区间：answer 一定落在 [left, right]
        while (left < right) {  // 区间未收敛就继续二分
            int mid = (left + right + 1) >> 1;  // 上取整中点，避免 left/right 相邻时死循环
            if (check(fonts[mid])) {  // 该字号可行，说明答案至少是 mid
                left = mid;  // 收缩左边界到 mid
            } else {  // 该字号太大了
                right = mid - 1;  // 收缩右边界到 mid 的前一个位置
            }
        }
        return check(fonts[left]) ? fonts[left] : -1;  // 收敛点可行就返回该字号，否则一个都放不下返回 -1
    }
};