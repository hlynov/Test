
(setq inhibit-startup-message t)  ;;не показывать сообщение при старте
(fset 'yes-or-no-p 'y-or-n-p)  ;;не заставляйте меня печать yes целиком
(fset 'yes-or-no-p 'y-or-n-p)  ;;не заставляйте меня печать yes целиком

;;=======================
;выводим в буфер сообщений
(message "start .emacs loading")
;засекаем время начала загрузки
(setq emacs-load-start-time (current-time))
;;используем Common Lisp
(require 'cl)
;;


;;на запросы отвечаем коротко
(defalias 'yes-or-no-p 'y-or-n-p)

;;автоматически отображаем линейку
(add-hook 'window-configuration-change-hook (lambda () (ruler-mode 1)))
;;установка размеров экрана
(set-frame-height (selected-frame) 55)
(set-frame-width (selected-frame) 100)
;;установка левого верхнего угла фрейма
(set-frame-position (selected-frame) 60 0)
;;в строке состояния показываем номера строки, колонки, размер файла
(setq column-number-mode t)
(setq line-number-mode t)
(size-indication-mode t)
;;нумеровать строки в левой части окна
(global-linum-mode 1)



;;корректируем цвет выделенного текста
(set-face-attribute 'region nil :background "gray38" :foreground "white")
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Устанавливаем основной шрифт
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Подсветка синтаксиса
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;показывать помеченный текст
;(setq transient-mark-mode '1);ON by default v23+
(setq font-lock-maximum-decoration t)
;;подсветка синтаксиса всегда
(global-font-lock-mode t)
;;Выделение парных скобок
(show-paren-mode 1)

(global-set-key "\C-x\C-b" 'buffer-menu)

(setq mode-line-system-identification  
  (substring (system-name) 0
             (string-match "\\..+" (system-name))))

(setq default-mode-line-format
      (list ""
            'mode-line-modified
            "<"
            'mode-line-system-identification
            "> "
            "%14b"
            " "
            'default-directory
            " "
            "%[(" 
            'mode-name 
            'minor-mode-alist 
            "%n" 
            'mode-line-process  
            ")%]--" 
             "Line %l--"
            '(-3 . "%P")
            "-%-"))

;; Установим новый формат по умолчанию.
(setq mode-line-format default-mode-line-format)


;;========================================
;;Назначение клавиш
;;========================================


(global-set-key [f1]    'help)
(global-set-key [f2]    'bookmark-set)
(global-set-key [f3]    'bookmark-jump)
(global-set-key [f12]    'compile)
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(ede-project-directories
   (quote
    ("/home/admin/Documents/programming/Cpp/TestPro/cppLess4"))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
