#!/usr/bin/perl

# Scipt parses files in format of these cheatsheets
# and looks for patterns only in descriptions
# (lines starting with "#")
# Add path to another files of this format to array @other_files below
# if you need it.

use warnings;
use strict;

use Term::ANSIColor;

my $dir = $ENV{"HOME"} . "/Cheatsheets";
my @other_files = ();

if (! -d $dir) {
    print "Can't find cheatsheets directory\n";
    exit 1
}

chdir $dir;

sub usage() {
    print "Usage: $0 <search pattern>\n";
    exit 2
}

if (@ARGV < 1) {usage};

my $pattern = join (" ", @ARGV);
print "Looking for $pattern\n";

#my @files = `find ./ -maxdepth 1 -type f`;
my @files = <*>;
my $printable = 0;


push @files, @other_files;
    
foreach my $file (@files) {
    open (my $F, "<", $file) if (-f $file)
	|| die "Can't open $file: $!";
    while ((<$F>)) {
	chomp;
	print "$_\n" if $printable;
	if (/^#/ && /$pattern/i) {
	    $printable = 1;
	    print color ("red"), $file, color ("reset");
	    print ":\t";
	    print color ("green"), "$_\n", color ("reset");;
	}
	$printable = 0 if (/^$|^==/ || eof);
    }
    close $F
    
}
