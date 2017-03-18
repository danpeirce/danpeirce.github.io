#! perl -w

use strict;
use Tk;
use Win32::SerialPort;
use Time::HiRes qw( usleep gettimeofday tv_interval  stat );

my $ob = Win32::SerialPort->new ('COM1') || die;

$ob->user_msg(1); 	# misc. warnings
$ob->error_msg(1); 	# hardware and data errors

$ob->baudrate(115200);
$ob->parity("none");
$ob->databits(8);
$ob->stopbits(1);
$ob->handshake("none");

$ob->write_settings;

my $result;
my $mresult;

$ob->read_interval(0);
$ob->read_const_time(10000);

$ob->write("u");
my $time_us = 250000;
usleep ($time_us);
$result = $ob->input;
print "$result";
#while ( $result !~ m/\?/ ) 
#{
#    $ob->write("u");
#    usleep ($time_us);
#    $result = $ob->input;
#    print "$result";
#}

my $mw = MainWindow->new;
my $motorw;
my $leftw;
my $rightw;
my $sensorw;
my $threshholdw;
my $jogw;

$mw->title("Robot Diagnostic Control - Top");

$mw->Button(-text => "Exit", -command =>sub {$mw->destroy}) -> pack( -anchor => 'w');
$mw->Label(-text => " ") -> pack( -anchor => 'w');

$mw->Label(-text => "Messages from the robot appear in the Perl text window") ->pack;
$mw->Button(-text => "up - menu item", -command => sub {$ob->write("u");}) -> pack;
$mw -> Label(-text=>" ") ->pack;
my $bframe = $mw->Frame( -borderwidth => 2, -relief => 'groove');
$bframe->Button(-text => "motor", -command => \&motor_command) 
                                       ->pack( -side => 'left', -anchor => 'n');

$bframe->Button(-text => "sensor", -command => \&sensor_command) 
                                       ->pack( -side => 'left', -anchor => 'n');
$bframe -> pack;

#$mw->Button(-text => "Restart Com", -command => \&restart_com ) -> pack( -anchor => 'w');

$mw -> repeat(30,\&update);  # updates text window every 30ms

MainLoop;

usleep ($time_us);
$result = $ob->input;
print "$result";

undef $ob;

#---------------------------------------------------------------------------
# sub get_msg
# {
#    $mw -> after(30);  # waits 30ms for data transfer from robot
#    $result = $ob->input;
#    print "$result";
#}

sub close_motor
{
  $ob->write("u");
  $motorw->withdraw; 
  $mw -> deiconify();
  $mw->raise();
}

sub motor_command
{
   $mw -> withdraw;
   $ob->write("m");
   if (! Exists($motorw)) 
   {
     $motorw = $mw->Toplevel();
     $motorw->title("Motor");
     $motorw->Button(-text => "Close - up", -command => \&close_motor)->pack( -anchor => 'w');
     $motorw->Label(-text => " ") -> pack( -anchor => 'w');
     my $motorbframe = $motorw->Frame( -borderwidth => 2, -relief => 'groove');
     $motorbframe->Button(-text => "left", -command => \&left_command) 
        -> pack( -side => 'left', -anchor => 'n');
     $motorbframe->Button(-text => "right", -command => \&right_command) 
        -> pack( -side => 'left', -anchor => 'n');
     $motorbframe->Button(-text => "brake all", -command =>sub {$ob->write("b");}) 
        ->pack( -side => 'left', -anchor => 'n');
     $motorbframe->Button(-text => "Jog sequence", -command =>\&jog_command) 
        ->pack( -side => 'left', -anchor => 'n');
     $motorbframe->pack;

   }
   else
   {
     $motorw -> deiconify();
     $motorw->raise();
   }

}


sub close_left
{
  $ob->write("u");
  $leftw->withdraw;
  $motorw -> deiconify();
  $motorw->raise();
}

sub left_command
{
#   my $lresult;

   $motorw -> withdraw;
   $ob->write("l");
   if (! Exists($leftw)) 
   {
     $leftw = $motorw->Toplevel();
     $leftw->title("Left");
     $leftw->Button(-text => "Close - up", -command => \&close_left )-> pack( -anchor => 'w');
     $leftw->Label(-text => " ") -> pack( -anchor => 'w');
     my $bleftframe = $leftw->Frame( -borderwidth => 2, -relief => 'groove');     
     $bleftframe->Button(-text => "fast", -command => sub {$ob->write("f");}) 
                                       ->pack( -side => 'left', -anchor => 'n');
     $bleftframe->Button(-text => "medium", -command =>sub {$ob->write("m");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bleftframe->Button(-text => "slow", -command =>sub {$ob->write("s");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bleftframe->Button(-text => "reverse", -command =>sub {$ob->write("<");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bleftframe->Button(-text => "forward", -command =>sub {$ob->write(">");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bleftframe->Button(-text => "coast", -command =>sub {$ob->write("c");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bleftframe -> pack;

   }
   else
   {
     $leftw -> deiconify();
     $leftw->raise();
   }

}

sub close_right
{
  $ob->write("u");
  $rightw->withdraw;
  $motorw -> deiconify();
  $motorw->raise();
}

sub right_command
{
 #  my $rresult;

   $motorw -> withdraw;
   $ob->write("r");
   if (! Exists($rightw)) 
   {
     $rightw = $motorw->Toplevel();
     $rightw->title("Left");
     $rightw->Button(-text => "Close - up", -command => \&close_right )-> pack( -anchor => 'w');
     $rightw->Label(-text => " ") -> pack( -anchor => 'w');
     my $brightframe = $rightw->Frame( -borderwidth => 2, -relief => 'groove');     
     $brightframe->Button(-text => "fast", -command => sub {$ob->write("f");}) 
                                       ->pack( -side => 'left', -anchor => 'n');
     $brightframe->Button(-text => "medium", -command =>sub {$ob->write("m");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $brightframe->Button(-text => "slow", -command =>sub {$ob->write("s");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $brightframe->Button(-text => "reverse", -command =>sub {$ob->write("<");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $brightframe->Button(-text => "forward", -command =>sub {$ob->write(">");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $brightframe->Button(-text => "coast", -command =>sub {$ob->write("c");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $brightframe -> pack;

   }
   else
   {
     $rightw -> deiconify();
     $rightw->raise();
   }
#    $rightw -> after(30);  # waits 30ms for data transfer from robot
#    $result = $ob->input;
#    print "$result";
}

sub close_sensor
{
  $ob->write("u");
  $sensorw->withdraw;
  $mw -> deiconify();
  $mw->raise();
}

sub sensor_command
{

   $mw -> withdraw;
   $ob->write("s");
   if (! Exists($sensorw)) 
   {
     $sensorw = $mw->Toplevel();
     $sensorw->title("Sensor");
     $sensorw->Button(-text => "Close - up", -command => \&close_sensor )-> pack( -anchor => 'w');
     $sensorw->Label(-text => " ") -> pack( -anchor => 'w');
     my $bsensorframe = $sensorw->Frame( -borderwidth => 2, -relief => 'groove');     
     $bsensorframe->Button(-text => "sensor 1", -command => sub {$ob->write("1");}) 
                                       ->pack( -side => 'left', -anchor => 'n');
     $bsensorframe->Button(-text => "sensor 2", -command =>sub {$ob->write("2");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bsensorframe->Button(-text => "sensor 3", -command =>sub {$ob->write("3");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bsensorframe->Button(-text => "sensor 4", -command =>sub {$ob->write("4");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bsensorframe->Button(-text => "sensor 5", -command =>sub {$ob->write("5");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bsensorframe->Button(-text => "set threshhold", -command => \&threshhold_command)
                                       ->pack( -side => 'left', -anchor => 'n');
     $bsensorframe->Button(-text => "automatic set threshhold", -command =>sub {$ob->write("a");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bsensorframe -> pack;

   }
   else
   {
     $sensorw -> deiconify();
     $sensorw->raise();
   }

}

sub close_threshhold
{
  $ob->write("u");
  $threshholdw->withdraw;
  $sensorw -> deiconify();
  $sensorw->raise();
}

sub threshhold_command
{

   $sensorw -> withdraw;
   $ob->write("t");
   if (! Exists($threshholdw)) 
   {
     $threshholdw = $sensorw->Toplevel();
     $threshholdw->title("Threshhold");
     $threshholdw->Button(-text => "Close - up", -command => \&close_threshhold )-> pack( -anchor => 'w');
     $threshholdw->Label(-text => " ") -> pack( -anchor => 'w');
     my $bthreshholdframe = $threshholdw->Frame( -borderwidth => 2, -relief => 'groove');
     $bthreshholdframe->Button(-text => "0", -command => sub {$ob->write("0");}) 
                                       ->pack( -side => 'left', -anchor => 'n');     
     $bthreshholdframe->Button(-text => "1", -command => sub {$ob->write("1");}) 
                                       ->pack( -side => 'left', -anchor => 'n');
     $bthreshholdframe->Button(-text => "2", -command =>sub {$ob->write("2");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bthreshholdframe->Button(-text => "3", -command =>sub {$ob->write("3");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bthreshholdframe->Button(-text => "4", -command =>sub {$ob->write("4");})
                                       ->pack( -side => 'left', -anchor => 'n');
     $bthreshholdframe->Button(-text => "5", -command =>sub {$ob->write("5");})
                                       ->pack( -side => 'left', -anchor => 's');
     $bthreshholdframe->Button(-text => "6", -command => sub {$ob->write("6");}) 
                                       ->pack( -side => 'left', -anchor => 's');     
     $bthreshholdframe->Button(-text => "7", -command => sub {$ob->write("7");}) 
                                       ->pack( -side => 'left', -anchor => 's');
     $bthreshholdframe->Button(-text => "8", -command =>sub {$ob->write("8");})
                                       ->pack( -side => 'left', -anchor => 's');
     $bthreshholdframe->Button(-text => "9", -command =>sub {$ob->write("9");})
                                       ->pack( -side => 'left', -anchor => 's');

     $bthreshholdframe -> pack;
     $threshholdw->Label(-text => " ") -> pack( -anchor => 'w');
     $threshholdw->Button(-text => "enter", -command => \&close_threshhold)
                                       ->pack( -side => 'right', -anchor => 's');


   }
   else
   {
     $threshholdw -> deiconify();
     $threshholdw->raise();
   }

}

sub close_jog
{
  $ob->write("u");
  $jogw->withdraw; 
  $motorw -> deiconify();
  $motorw->raise();
}

sub jog_command
{
   $motorw -> withdraw;
   $ob->write("j");
   if (! Exists($jogw)) 
   {
     $jogw = $motorw->Toplevel();
     $jogw->title("Jog");
     $jogw->Button(-text => "Close - up", -command => \&close_jog)->pack( -anchor => 'w');
     $jogw->Label(-text => " ") -> pack( -anchor => 'w');
     my $jogbframe = $jogw->Frame( -borderwidth => 2, -relief => 'groove');
     $jogbframe->Button(-text => "1", -command =>sub {$ob->write("1");}) 
        -> pack( -side => 'left', -anchor => 'n');
     $jogbframe->Button(-text => "2", -command =>sub {$ob->write("2");}) 
        -> pack( -side => 'left', -anchor => 'n');
     $jogbframe->pack;

   }
   else
   {
     $jogw -> deiconify();
     $jogw->raise();
   }
#   $jogw -> repeat(30,\&update);  # updates text window every 30ms

}

sub update
{
   $result = $ob->input;
   print "$result";
   if ($result =~ m/<POR>/) 
   { 
      print "\nRobot Power On Reset detected --- wait...\n"; 
      if(Exists($threshholdw)) { &close_threshhold; }
      if(Exists($jogw)) { &close_jog; }
      if(Exists($leftw)) { &close_left; }
      if(Exists($rightw)) { &close_right; }
      if(Exists($motorw)) { &close_motor; }
      if(Exists($sensorw)) { &close_sensor; }
      if(Exists($mw)) { $mw -> withdraw; }
      while( $result !~ m/\?/ ) {$result = $ob->input; print "$result";}
      $mw -> deiconify();
      $mw->raise();
   }
   if ($result =~ m/<BOR>/) 
   { 
      print "\nRobot Brown out Reset detected --- wait...\n"; 
      if(Exists($threshholdw)) { &close_threshhold; }
      if(Exists($jogw)) { &close_jog; }
      if(Exists($leftw)) { &close_left; }
      if(Exists($rightw)) { &close_right; }
      if(Exists($motorw)) { &close_motor; }
      if(Exists($sensorw)) { &close_sensor; }
      if(Exists($mw)) { $mw -> withdraw; }
      print "Must cycle Robot Power Off and On!";
   }
   if ($result =~ m/<LVD>/) 
   { 
      print "\nRobot Low Voltage detected --- wait...\n"; 
      if(Exists($threshholdw)) { &close_threshhold; }
      if(Exists($jogw)) { &close_jog; }
      if(Exists($leftw)) { &close_left; }
      if(Exists($rightw)) { &close_right; }
      if(Exists($motorw)) { &close_motor; }
      if(Exists($sensorw)) { &close_sensor; }
      if(Exists($mw)) { $mw -> withdraw; }
      print "Must cycle Robot Power Off and On!";
   }
   if ($result =~ m/<WDT>/) 
   { 
      print "\nRobot Watchdog time fault detected --- wait...\n"; 
      if(Exists($threshholdw)) { &close_threshhold; }
      if(Exists($jogw)) { &close_jog; }
      if(Exists($leftw)) { &close_left; }
      if(Exists($rightw)) { &close_right; }
      if(Exists($motorw)) { &close_motor; }
      if(Exists($sensorw)) { &close_sensor; }
      if(Exists($mw)) { $mw -> withdraw; }
      print "Must cycle Robot Power Off and On!";
   }
}

sub restart_com
{
  undef $ob;
  my $ob = Win32::SerialPort->new ('COM1') || die;

  $ob->user_msg(1); 	# misc. warnings
  $ob->error_msg(1); 	# hardware and data errors

  $ob->baudrate(115200);
  $ob->parity("none");
  $ob->databits(8);
  $ob->stopbits(1);
  $ob->handshake("none");

  $ob->write_settings;

  my $result;
  my $mresult;

  $ob->read_interval(0);
  $ob->read_const_time(10000);

  $ob->write("u");
  my $time_us = 250000;
  usleep ($time_us);
  $result = $ob->input;
  print "$result";
}