<? # txt2tags.php - a handy web interface for the txt2tags conversion tool
   # 2002-03-22 Aurelio Marinho Jargas <verde@aurelio.net>
   # 2004-06-26 Aurelio: v2.0: %%date, photo, s/orange/blue/, XHTML target,
   #            CSS, work in new PHP, --enum-title, show parsed x?html
   # 2004-10-20 Aurelio: v2.1: Text capitalized, using button instead photo
   # 2004-12-28 Aurelio: v2.2: Lout target
   # 2005-05-28 Aurelio: v2.3: link: s/sample.t2t/markup.html/, gray table

### CONFIG
## customize here your settings
#
# define here where's the txt2tags program location
$prog = "./txt2tags";
# the default text for the user's textarea
$dfttxt = "= My Title =\n";
$dfttxt.= "This is a __sample__ text line, with **bold** and //italic//.\n";
$dfttxt.= "\nToday is %%date(%c).\nAnd here is a nice pic: [img/t2tpowered.png].\n";
$dfttxt.= "\n  | John |  33  |    Male |\n  | Mary |  19  |  Female |";
#
### end CONFIG


function HtmlHelpTable($arr) {
$init = "<center><table align=\"center\" cellpadding=5 cellspacing=5 border=0>";
$tropen = '<tr>'; $trclose = '</tr>';
$tdopen = '<td nowrap bgcolor="white" valign="top"><font size=2>';
$tdclose = '</font></td>'; $end = '</center></table>';

$r = "\n$init\n";                        # open table
while (list($key, $celldata) = each($arr)) {
  $r .= "$tropen\n";                     # open line
  for ($j=0;$j<count($celldata);$j++) {
    $data = $celldata; if (is_array($celldata)) $data = $celldata[$j];
    $r .= "$tdopen$data$tdclose\n";      # full cell
  }
  $r .= "$trclose\n";                    # close line
}
$r .= "$end\n\n";                        # close table
return $r;
}
function FormSelect($name,$arr,$selected='',$size=0) {
  $dft_size = 10;
  if ($size == 0){  # case not specified, $size = $array size
    $arrsize = count($arr);
    if ($arrsize < $dft_size) $size = $arrsize;
    else $size = $dft_size;
  }
  $r = "\n<select name=\"$name\" size=$size class=\"Form\">\n";
  while (list($key, $data) = each($arr)) {
    $id = $txt = $data; if (is_array($data)) list($id, $txt) = $data;
    $sel = ''; if ($id == $selected) $sel .= " selected";
    $r .= "<option value=\"$id\"$sel>$txt</option>\n";
  }
  $r .= "</select>\n";
  return $r;
}
function FormClose()   { print "\n</form>"; }
function FormOpen($url){ print "\n<form method=\"post\" action=\"$url\">"; }
function FormHidden($name, $value){
  return "\n<input type=\"hidden\" name=\"$name\" value=\"$value\">"; }
function FormSubmit($txt){
  return "\n<input type=\"submit\" value=\"$txt\">"; }
function FormTextarea($name, $txt, $cols=40, $lines=3){
  return "\n<textarea name=\"$name\" cols=$cols rows=$lines>$txt</textarea>"; }
function FormCheck($name, $value, $on=0){ if ($on) $state = 'checked';
  return "\n<input type=\"checkbox\" name=\"$name\" value=\"$value\" $state>"; }
function getvar($name){
  eval('global $'.$name.';');         # first try the global one
  eval('$val = $'.$name.';');
  if (!$val) $val = $_SERVER[$name];  # if not found, try others
  if (!$val) $val = $_POST[$name];
  # print "<p>key: <b>$name</b>, value: <b>$val</b>---</p>"; 
  return $val;
}
?>

<html>
<head><title>txt2tags // ONE source, MULTI targets</title>

<style type="text/css">
  body  { background-color:#ddeeff; color:black; margin:2em; }
  a     { text-decoration:none; }
  h1    { text-align:center; background-color:blue; color:white; padding:8px; }
  h2    { padding-top:20px; }
  hr    { border-style:none; }
  code  { background-color:white; }
  table { border-style:solid; border-color:black; }
  div.output pre {
    background-color:lightblue; padding:8px; border-color:black;
    border-style:solid; border-width:1px 1px; }
  a:hover   { color:red; }
  a:visited { color:purple; }
</style>

</head>
<body bgcolor="white" text="black">

<h1>txt2tags WEB Interface</h1>


<ul>
<li><a href="http://txt2tags.sf.net">Txt2tags</a> is a text formatting
    and conversion tool and this is its WEB Interface.

<li>On this page you can try it out <b>before</b> download.

<li>This page is included on the program distribution, so you can
    install and use it on your own intranet!</p>
</ul>

<p>
<hr>
<center><p align="center">

<?
$myself    = getvar('PHP_SELF');
$txt       = getvar('txt');
$target    = getvar('target');
$noheaders = getvar('noheaders');
$enumtitle = getvar('enumtitle');

if (!$txt) $txt = $dfttxt;

#--[ help ]----------------------------------------------------------
$arr_simplehelp[] = array(
   '<code>**bold**</code>', '<code>//italic//</code>',
   '<code>__underline__</code>', '<code>``code``</code>',
   '<code>[image.jpg]</code>', '<code>%%date</code>');
$arr_multihelp[] = array(
   "<pre>- list\n  - sublist\n    - subsu...</pre>",
   "<pre>```\nverbatim area\n```</pre>",
   "<pre>= title =\n== subtitle ==\n=== subsub...===</pre>",
   "<pre>|| title | title |\n|  cell  | cell  |\n|  cell  | cell  |</pre>");

print "\n".'<table cellspacing=0 cellpadding=2 border=0 bgcolor="gray">';
print "\n".'<tr><td><p align="center"><font color="white"><b>- MARKUP -</b></font></p></td></tr>';
print "\n".'<tr><td>'.HtmlHelpTable($arr_simplehelp).'</td></tr>';
print "\n".'<tr><td>'.HtmlHelpTable($arr_multihelp ).'</td></tr>';
print "\n".'<tr><td><p align="right"><font color="white"><b>';
print '<a href="http://txt2tags.sf.net/markup.html">Complete markup reference</a>&nbsp;</td></tr>';
print "\n</table>\n";
#--------------------------------------------------------------------
# try to find this filename and location

print FormOpen($myself);
print '<p>'.FormTextarea('txt', $txt, 70, 8);
print '<br>Target:'.FormSelect('target', array(
       array('html' , 'HTML page'),
       array('xhtml', 'XHTML page'),
       array('sgml' , 'SGML document'),
       array('tex'  , 'LaTeX document'),
       array('lout' , 'Lout document'),
       array('man'  , 'UNIX Manual page'),
       array('mgp'  , 'Magic Point presentation'),
       array('moin' , 'MoinMoin page'),
       array('pm6'  , 'PageMaker 6.0 document')
       ), $target,1);
print FormCheck('noheaders', '--no-headers', $noheaders)." No headers";
print FormCheck('enumtitle', '--enum-title', $enumtitle)." Enumerate titles";
print '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
print FormSubmit('Convert!');
print FormClose();
print '</p></center><hr>';

if ($target){
  $txt = escapeshellarg("\n$txt"); # always empty headers
  $cmd = ereg_replace('[^a-z6 -]','',"-o- $noheaders $enumtitle -t $target -");
  print '<div class="output" id="output">';
  print "\n<h2>Text converted to ".strtoupper($target)."</h2>";
  print "\n<hr>\n\n<pre><code>";
  print "<font color=\"blue\"><b>COMMAND:</b></font> txt2tags $cmd";
  print "\n\n<font color=\"blue\"><b>OUTPUT:</b></font>\n";
  print htmlspecialchars(`echo $txt | $prog $cmd`);
  print "\n</code></pre>";
  if ($target == 'html' or $target == 'xhtml') {
    print "<h2>".strtoupper($target)." parsed</h2>\n";
    print "<table bgcolor=\"lightblue\"><tr><td>\n";
    print `echo $txt | $prog -H $cmd`;
    print "</td></tr></table>";
  }
  print "<hr></div>";
}
?>

<br>
Txt2tags site: <a href="http://txt2tags.sf.net">http://txt2tags.sf.net</a>
<br>Author: <a href="http://aurelio.net/en/">Aurelio Marinho Jargas</a>
</body>
</html>
