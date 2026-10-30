// 题目：2271. 毯子覆盖的最多白色砖块数（Maximum White Tiles Covered by a Carpet）
// 思路：按区间起点排序后用双指针滑动窗口，i 是毯子左端所在区间、j 是窗口右边界；窗口内完整覆盖的区间砖数记入 s，毯子若伸进下一个区间则再补上部分覆盖的砖数，过程中取最大值。
// 时间复杂度：O(n log n)，排序主导，双指针各只前进一次；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {  // tiles：若干 [起点, 终点] 的白色砖块区间；carpetLen：毯子长度
        sort(tiles.begin(), tiles.end());  // 按区间起点升序排序，保证窗口内区间连续、便于双指针推进
        int s = 0, ans = 0, n = tiles.size();  // s：窗口内被完整覆盖区间的砖块总数；ans：历史最大覆盖数；n：区间个数
        for (int i = 0, j = 0; i < n; ++i) {  // i 指向毯子左端所在的区间，j 为窗口右边界（初始都从 0 开始）
            while (j < n && tiles[j][1] - tiles[i][0] + 1 <= carpetLen) {  // 区间 j 能被毯子完整覆盖时，直接把它的砖数全部计入窗口
                s += tiles[j][1] - tiles[j][0] + 1;  // 该区间砖块数 = 终点 - 起点 + 1，累加到窗口和
                ++j;  // 右边界右移，尝试纳入下一个区间
            }  // 完整覆盖的区间扩展结束
            if (j < n && tiles[i][0] + carpetLen > tiles[j][0]) {  // 毯子右端落进了下一个区间的内部，只能部分覆盖
                ans = max(ans, s + tiles[i][0] + carpetLen - tiles[j][0]);  // 完整区间砖数加上被部分覆盖的砖数（毯子右端 - 该区间起点）
            } else {  // 毯子右端没有触及下一个区间
                ans = max(ans, s);  // 那就只能拿到完整覆盖区间的砖数
            }  // 两种情况取最优后，把区间 i 移出窗口，为左边界右移做准备
            s -= (tiles[i][1] - tiles[i][0] + 1);  // 移出区间 i 时减去它的砖块数，保证 s 始终是当前窗口之和
        }  // 所有起点都枚举完毕
        return ans;  // 返回最多能覆盖的白砖块数
    }  // 解题方法结束
};  // 题解类结束