# PowerRouting for OMNeT++ - plot.pl
# Marcel Ebbrecht, marcel.ebbrecht@googlemail.com
# free software, see LICENSE.md for details

### includes
use Statistics::Lite qw(:all);
use Chart::Gnuplot;
use DateTime qw();
use Switch;

### imports
require "./subs.pl";

### reading variables from commandline
# program mode
my $mode = $ARGV[0];

### execution
# mode switch
switch($mode) {
	case "singleCapacity" {	
		# get parameters
		my $dropoutInterval = $ARGV[2];
		my $shortTime = $ARGV[3];
		
		# filenames
		my $capacityOriginalFile = "results/$ARGV[1]-CapacityOverTime.csv";
		my $capacityOverTimeCsvFile = "results/$ARGV[1]-CapacityOverTime-Clean.csv";
		my $capacityOverTimeCsvFileShort = "results/$ARGV[1]-CapacityOverTime-Clean-Short.csv";
		my $capacityAtEndCsvFile = "results/$ARGV[1]-CapacityAtEnd-Clean.csv";
		my $capacityAtEndCsvFileShort = "results/$ARGV[1]-CapacityAtEnd-Clean-Short.csv";
		my $capacityAtEndPlotFile = "export/$ARGV[1]-CapacityAtEnd.png";
		my $capacityAtEndPlotFileShort = "export/$ARGV[1]-CapacityAtEnd-Short.png";
		my $capacityAtEndPlotTitle = "$ARGV[1]";
		my $capacityAtEndPlotTitleShort = "$ARGV[1] (".$shortTime."s)";
		
		# create csv for external plot
		my @resultsCapacity = getCapacityResults($capacityOriginalFile, $dropoutInterval);
		my @resultsCapacityShort = getCapacityResultsShort($shortTime, @resultsCapacity);
		my @resultsCapacityAtEnd = getMinimumCapacityValues(@resultsCapacity);
		my @resultsCapacityShortAtEnd = getMinimumCapacityValues(@resultsCapacityShort);
		writeCapacityArrayToCsv($capacityOverTimeCsvFile, @resultsCapacity);
		writeCapacityArrayToCsv($capacityOverTimeCsvFileShort, @resultsCapacityShort);
		writeCapacityArrayToCsv($capacityAtEndCsvFile, @resultsCapacityAtEnd);
		writeCapacityArrayToCsv($capacityAtEndCsvFileShort, @resultsCapacityShortAtEnd);
		
		# plot charts
		plotCapacityAtEnd($capacityAtEndPlotFile, $capacityAtEndPlotTitle, @resultsCapacityAtEnd);
		plotCapacityAtEnd($capacityAtEndPlotFileShort, $capacityAtEndPlotTitleShort, @resultsCapacityShortAtEnd);
		break;
	}
	
	case "compareProtocol" {
		# get parameters
		shift;
	    my $protcolFamily = $ARGV[0];
		shift;
	    my $numberOfRuns = $ARGV[0];
		shift;
		my @configurations = @ARGV;
		
		my @capacityAtEndDataStatistics = getCapacityAtEndStatistic($numberOfRuns, 1, @configurations);
		my @capacityAtEndDataStatisticsShort = getCapacityAtEndStatistic($numberOfRuns, 0, @configurations);
		
		break;
	}
}

