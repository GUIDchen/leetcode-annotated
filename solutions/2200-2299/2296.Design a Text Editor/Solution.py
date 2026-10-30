# 题目：2296. 设计一个文本编辑器（Design a Text Editor）
# 思路：用「光标左侧字符 + 光标右侧字符」两个列表当栈，编辑只动左侧，移动光标时在两栈之间搬字符。
# 时间复杂度：addText O(|text|)，deleteText 与 cursor 移动 O(k)；空间复杂度：O(n)，n 为文本总长。
class TextEditor:  # 用两个列表当栈，分别保存光标左侧和光标右侧的字符
    def __init__(self):  # 构造函数：两栈都为空，光标在文本开头
        self.left = []  # left：光标左侧字符，列表尾部就是光标前一个字符
        self.right = []  # right：光标右侧字符，逆序存放，列表尾部紧贴光标

    def addText(self, text: str) -> None:  # 在光标处插入 text：整段接到左侧栈顶
        self.left.extend(list(text))  # 用 extend 批量追加，避免逐个 append

    def deleteText(self, k: int) -> int:  # 删除光标前最多 k 个字符，返回实际删除数
        k = min(k, len(self.left))  # 实际删除数不能超过左侧字符总数
        for _ in range(k):  # 连续退格 k 次
            self.left.pop()  # 每次弹出左侧栈顶，即删除光标前一个字符
        return k  # 返回实际删除的字符数

    def cursorLeft(self, k: int) -> str:  # 光标左移 k 次，返回移动后光标左侧最后 10 个字符
        k = min(k, len(self.left))  # 最多只能移到文本开头
        for _ in range(k):  # 逐次左移
            self.right.append(self.left.pop())  # 左侧栈顶字符搬到右侧栈顶，光标随之左移
        return ''.join(self.left[-10:])  # 切片取左侧末尾至多 10 个字符

    def cursorRight(self, k: int) -> str:  # 光标右移 k 次，返回光标左侧最后 10 个字符
        k = min(k, len(self.right))  # 最多只能移到文本末尾
        for _ in range(k):  # 逐次右移
            self.left.append(self.right.pop())  # 右侧栈顶字符搬回左侧，光标随之右移
        return ''.join(self.left[-10:])  # 返回光标左侧最后 10 个字符


# 下面是 LeetCode 判题器自动生成的调用示例，属于注释，不是算法代码
# Your TextEditor object will be instantiated and called as such:
# obj = TextEditor()
# obj.addText(text)
# param_2 = obj.deleteText(k)
# param_3 = obj.cursorLeft(k)
# param_4 = obj.cursorRight(k)
