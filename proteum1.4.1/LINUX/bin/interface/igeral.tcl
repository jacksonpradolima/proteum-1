#------------------------------------------------------------------------------#
#   IGERAL.TCL
#   General functions for user interface.
#   author: Elisa Yumi Nakagawa
#   date: 02/21/96
#   last update: 07/02/96
#------------------------------------------------------------------------------#


#------------------------------------------------------------------------------#
#   Set_Busy
#   Sets mouse pointer as busy/nobusy.
#   date: 10/11/96
#   last update: 10/11/96, 11/18/96
#------------------------------------------------------------------------------#

proc Set_Busy {option} {  

   if {[string compare $option ON] == 0} {
      .proteum config -cursor watch
      .fp      config -cursor watch

      if [winfo exists .proteum.muta.m.dlg] {
         .proteum.muta.m.dlg config -cursor watch
         if [winfo exists .proteum.muta.m.dlg.f2.f1.f2.t] {
            .proteum.muta.m.dlg.f2.f1.f2.t config -cursor watch
            .proteum.muta.m.dlg.f2.f2.f2.t config -cursor watch
         }
      }
      update idletasks;      # Force a display update
   } else {
      .proteum config -cursor top_left_arrow
      .fp      config -cursor top_left_arrow

      if [winfo exists .proteum.muta.m.dlg] {
         .proteum.muta.m.dlg config -cursor top_left_arrow
         if [winfo exists .proteum.muta.m.dlg.f2.f1.f2.t] {
            .proteum.muta.m.dlg.f2.f1.f2.t config -cursor top_left_arrow
            .proteum.muta.m.dlg.f2.f2.f2.t config -cursor top_left_arrow
         }
      }
   }
}


#------------------------------------------------------------------------------#
#    MESSAGE {}
#    Print error message.
#    date: 03/21/96
#    last update: 05/06/96, 09/19/96
#------------------------------------------------------------------------------#

proc message {text} {
   toplevel .msg
   wm title .msg "Message"
   wm iconname .msg "MESSAGE"
   wm geometry .msg +155+190

   label .msg.title -text $text
   pack .msg.title -padx 20 -pady 10

   frame  .msg.f1 -bd 1 -relief sunken
   pack   .msg.f1 -pady 10
   button .msg.f1.ok -text "   OK   " -command {set ok 1}
   pack   .msg.f1.ok -padx 2 -pady 2

   tkwait visibility .msg;  # Waits the window .msg to become visible
   focus .msg.f1.ok
   grab  .msg
   tkwait variable ok
   grab release .msg

   destroy .msg
   return
}


#------------------------------------------------------------------------------#
#    MESSAGE_2B {}
#    Print error message in a two buttons window.
#    date: 03/21/96
#    last update: 05/06/96
#------------------------------------------------------------------------------#

proc message_2b {w msg} {
   toplevel .msg
   wm title .msg "Message"
   wm iconname .msg "MESSAGE"
   wm geometry .msg +155+190
  
   global maxtcase

   label .msg.title -text $msg
   pack  .msg.title -padx 20 -pady 10

   frame  .msg.f1  
   pack   .msg.f1 -pady 10 -padx 10

   frame  .msg.f1.f1 -borderwidth 1 -relief sunken 
   frame  .msg.f1.f2
   pack   .msg.f1.f1 .msg.f1.f2  -padx 4 -side left


   switch -exact $msg {

      "Program Test Already Exist !" {
         button .msg.f1.f1.cancel -text {  Cancel  } -command "
            set confirm 0"
         button .msg.f1.f2.confirm -text {Overwrite} -command "
            set confirm 1
            Create_New_Session
            destroy $w"
         pack .msg.f1.f1.cancel .msg.f1.f2.confirm -side left
      } 


      # A PARTE ABAIXO SOBRE CONFIRMAR CASO DE TESTE NAO ESTA' SENDO USADA
      "Confirm Test Case ?" {
         button .msg.f1.f1.cancel -text {  Cancel  } -command "
            Tcase DELETE [expr $maxtcase+1]
            set confirm 0
            pack forget .fp.t .fp.s"
         button .msg.f1.f2.confirm -text { Confirm } -command "
            set confirm 1
            pack forget .fp.t .fp.s"
         pack .msg.f1.f1.cancel .msg.f1.f2.confirm -side left
      }
   }


#   focus .msg.f1.f2.confirm
   focus .msg.f1.f1.cancel
   grab  .msg
   tkwait variable confirm
   grab release .msg
   
   destroy .msg
   return
}




#------------------------------------------------------------------------------#
#    LOAD_SRC {}
#    Loads source code of program (original and mutant) into text area.
#    OBS: last parameter nlinemut:
#                   0: loading original program
#                  -1: loading test case report
#         other value: loading mutant program
#
#    date: 04/22/96
#    last update: 07/02/96
#------------------------------------------------------------------------------#

proc Load_Src {filename textarea position} {
   set data ""
   if [catch {open $filename r} fileId] {
      message "Cannot Open File $filename !"
      return
   }
   $textarea config -state normal
   $textarea delete 1.0 end;          # Deletes last mutant of text area

   if {$position < 0 } {
     while { ! [eof $fileId] } {
	set data [read $fileId 1024]
	$textarea insert end $data
     }
   } else {
      incr position -1
      while { [eof $fileId] == 0 &&  $position > 0} {
        set quanto [min 1024 $position]
	set data [read $fileId $quanto]
	$textarea insert end $data
        incr position -$quanto
      }
     $textarea tag add $textarea.mutationhere 1.0 insert
     while { ! [eof $fileId] } {
	set data [read $fileId 1024]
	$textarea insert end $data
     }
   }
 
   close $fileId
}

proc HiLight {textarea ehmuta} {
   global test
   global muta
   set nline  0;     # Counts the number of lines
   set mline  0;     # First line in the file when the mutation occur
   set nchar0 0;     # Counts the number of character

   $textarea tag configure red -foreground red; # Color to arrow
   $textarea insert "$textarea.mutationhere.last linestart"  ">>" red
   $textarea see "$textarea.mutationhere.last linestart"
   return

   if [catch {open $filename r} fileId] {
      message "Cannot Open File $filename !"
      return
   } else {   
      $textarea config -state normal
      $textarea delete 1.0 end;          # Deletes last mutant of text area
      $textarea tag configure red -foreground red; # Color to arrow
 
      while {[gets $fileId line] >= 0} {
         incr nline;   # Increments number of lines

         set nchar1 [expr $nchar0 + [string length $line] + 1]

         # if the mutation is into the current line
         if {$muta(d_init0)>[expr $nchar0-1] && $muta(d_init0)<=$nchar1-1} {
            set mline $nline
 
            # If it is not mutant program then do "then" 
            if {$nlinemut == 0} {
               $textarea insert end ">>" red
               $textarea insert end "$line\n"
            } else {
               set mline $nlinemut
               $textarea insert end "$line\n"
            }
         } else {
            $textarea insert end "$line\n"
         }

         set nchar0 $nchar1

      }
      $textarea config -state disabled
      close $fileId
   }

   $textarea see [expr $mline-1].0
   return [expr $mline-1]
}



#------------------------------------------------------------------------------#
#   SHOW_FUNC {}
#   Shows list of functions.
#   date: 03/04/96
#   last update: 05/03/96, 09/19/96
#------------------------------------------------------------------------------#

proc Show_Func {type w} {
   wm geometry $w +10+65
 
   global MAXFUNCTIONS;     # Max number of functions
   global functions;        # Names of functions
   global index_func;       # Index related to each function
   global in;               # Input variables

   if {[string compare $type all] == 0 && [winfo ismapped $w.f8.t]} {
      pack forget $w.f9 $w.f9.confirm $w.f9.cancel
      pack forget $w.f8 $w.f8.t $w.f8.sv 
      for {set i 0} {$i < $MAXFUNCTIONS} {incr i} {
         destroy $w.f8.t.$i 
      }
      pack $w.f9
      pack $w.f9.confirm $w.f9.cancel -side left -pady 10
      wm geometry $w 500x225
      wm minsize  $w 500 225
      wm maxsize  $w 500 225



   } elseif {[string compare $type select] ==0 && ![winfo ismapped $w.f8.t]} {

      set in(dir)   [Blank_Space_Out $in(dir)]
      set in(src)   [Blank_Space_Out $in(src)]

      # Verifies if directory and source file exist
      if {![file isdirectory $in(dir)]} {
          message "Directory Does Not Exist!"    
          return
      } elseif {[string length $in(src)] == 0} {
          message "Invalid Program Test Name !"
          return
      } elseif {![file isfile $in(dir)/$in(src).c]} { ###% Modified
          message "Source File Does Not Exist!"
          return
      }

      Li NEWSES;        # Creates a LI file 
      Li LISTFUNC;      # Takes the list of functions 
 
      pack forget $w.f9 $w.f9.confirm $w.f9.cancel
      pack $w.f8 -pady 5
      pack $w.f8.t $w.f8.sv -side left -fill both
      
      for {set i 0} {$i < $MAXFUNCTIONS} {incr i} {
         frame $w.f8.t.$i
         pack  $w.f8.t.$i 
         $w.f8.t window create end -window $w.f8.t.$i 
         checkbutton $w.f8.t.$i.c$i -text $functions($i) \
	     -variable index_func($i)\
             -width 50 -selectcolor green -cursor hand2
	 set index_func($i) 0
         pack $w.f8.t.$i.c$i -fill x
      }

      pack $w.f9 
      pack $w.f9.confirm $w.f9.cancel -side left -pady 10

      wm geometry $w 500x340
      wm minsize  $w 500 340
      wm maxsize  $w 500 340
   }
}


#------------------------------------------------------------------------------#
#   ENABLE_MENUBUTTONS {}
#   Enables menu buttons if a test session is open.
#   date: 06/05/96
#   last update: 06/05/96
#------------------------------------------------------------------------------#

proc Enable_MenuButtons {} {
   .proteum.tcase  configure -state normal
   .proteum.muta   configure -state normal
   .proteum.report configure -state normal
   .proteum.status configure -state normal
}



#----------------------------------------------------------------------
proc min {a b} {
   if {$a <= $b} "return $a"
   return $b
}
