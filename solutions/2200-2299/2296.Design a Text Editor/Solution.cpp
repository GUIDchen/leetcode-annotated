// 题目：2296. 设计一个文本编辑器（Design a Text Editor）
// 思路：用「光标左侧串 + 光标右侧串」模拟，编辑只动左侧，移动光标时在两个串之间搬字符。
// 时间复杂度：addText O(|text|)，deleteText 与 cursor 移动 O(k)；空间复杂度：O(n)，n 为文本总长。
class TextEditor {  // 用「光标左侧串 + 光标右侧串」两个栈式字符串模拟文本编辑器
public:  // 对外接口
    TextEditor() {  // 构造函数：左右两侧都为空串，光标位于文本开头
    }

    void addText(string text) {  // 在光标处插入 text：等价于把 text 追加到左侧串末尾
        left += text;  // 插入后光标位于新文本之后，所以字符全部进入左侧
    }

    int deleteText(int k) {  // 删除光标前最多 k 个字符，返回实际删除的个数
        k = min(k, (int) left.size());  // 实际能删的字符数不超过左侧串长度
        left.resize(left.size() - k);  // 直接截短左侧串，即丢弃末尾 k 个字符
        return k;  // 返回实际删除的字符数
    }

    string cursorLeft(int k) {  // 光标左移 k 次，返回移动后光标左侧最后 10 个字符
        k = min(k, (int) left.size());  // 最多只能左移到文本开头
        while (k--) {  // 逐次左移；k-- 是先用后减，循环正好 k 次
            right += left.back();  // 左侧末尾字符移到右侧：right 逆序存放，栈顶紧贴光标
            left.pop_back();  // 从左侧串中移除该字符
        }
        return left.substr(max(0, (int) left.size() - 10));  // 截取左侧串末尾至多 10 个字符作为答案
    }

    string cursorRight(int k) {  // 光标右移 k 次，同样返回光标左侧最后 10 个字符
        k = min(k, (int) right.size());  // 最多只能右移到文本末尾
        while (k--) {  // 逐次右移 k 次
            left += right.back();  // 右侧栈顶（最靠近光标）的字符搬回左侧
            right.pop_back();  // 从右侧串中移除该字符
        }
        return left.substr(max(0, (int) left.size() - 10));  // 返回光标左侧最后 10 个字符
    }

private:  // 内部状态
    string left, right;  // left：光标左侧内容，末尾是光标前一个字符；right：光标右侧内容，逆序存放
};

// 下面是 LeetCode 判题器自动生成的调用示例，属于块注释，不是算法本体
/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */