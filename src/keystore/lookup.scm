#!/usr/bin/env scheme-r5rs
(define (filter prop list)
  (cond ((null? list) '())
        ((prop (car list)) (cons (car list) (filter prop (cdr list))))
        (else (filter prop (cdr list)))))
(define (match-record key value record)
  (let ((val (assoc key record)))
    (cond ((and (equal? (car val) key) (equal? (cdr val) value)) #t)
          (else #f))))
(define (keyfilt key value reclist)
  (filter (lambda (record) (match-record key value record))
          reclist))
(define (process-port port key value)
  (keyfilt key value (read port)))
(define (main args)
  (begin
    (display (process-port (open-input-file (cadr args)) (string->symbol
                                                        (caddr args))
                                            (cadddr args)))))