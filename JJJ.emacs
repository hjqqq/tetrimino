(require 'cc-mode)
(c-set-offset 'inline-open 0)
(c-set-offset 'friend '-)
(c-set-offset 'substatement-open 0)

(defun my-c-mode-common()
  (interactive)
  ;; 自动模式，在此种模式下当你键入{时，会自动根据你设置的对齐风格对齐
  (c-toggle-hungry-state)
  ;; TAB键的宽度设置为4
  (setq c-basic-offset 4)
  ;; 在菜单中加入当前Buffer的函数索引
  (imenu-add-menubar-index)
  ;; 在状态条上显示当前光标在哪个函数体内部
  ;(which-function-mode)
  )

(defun my-c-mode-hook()
  (interactive)
  ;; 将回车代替C-j的功能，换行的同时对齐
  (define-key c-mode-map [(return)] 'newline-and-indent)
  (define-key c-mode-map (kbd "C-j") 'newline-and-indent)
  (define-key c-mode-map (kbd "C-c C-b") 'compile)
  (c-set-style "linux") 
  (my-c-mode-common))

(defun my-c++-mode-hook()
  (interactive)
  ;; 将回车代替C-j的功能，换行的同时对齐
  (define-key c++-mode-map [(return)] 'newline-and-indent)
  (define-key c++-mode-map (kbd "C-j") 'newline-and-indent)
  (define-key c++-mode-map (kbd "C-c C-b") 'compile)
  (c-set-style "stroustrup") 
  (my-c-mode-common))

(add-hook 'c-mode-hook 'my-c-mode-hook)
(add-hook 'c++-mode-hook 'my-c++-mode-hook)
(add-to-list 'auto-mode-alist '("\\.h\\'" . c++-mode))
