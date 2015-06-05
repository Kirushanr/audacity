# Introduction #

This is an earlier experiment with using Google's issue tracker for Audacity. We've since then moved to Bugzilla.

Here are the default displays, first as a list, then as a grid.
  * [The default issue tracker report](http://code.google.com/p/audacity/issues/list).
  * [The default issue grid](http://code.google.com/p/audacity/issues/list?can=2&q=&colspec=ID+Summary+Priority+Type+Status&sort=&x=priority&y=type&cells=tiles&mode=grid)

Here are some 'canned' issue tracker queries:

  * [Issues by Platform](http://code.google.com/p/audacity/issues/list?can=2&q=&sort=-opsys+component&colspec=ID%20Opsys%20Priority%20Type%20Component%20Summary) - Windows / Vista / Mac / Linux
  * [Regressions](http://code.google.com/p/audacity/issues/list?can=2&q=label%3ARegression) - Features that worked in an earlier version and are currently broken.
  * [HeisenBugs](http://code.google.com/p/audacity/issues/list?can=2&q=label%3AMoonPhaseBug+OR+label%3AHeisenBug&colspec=ID+Summary+Priority+Status+Type&cells=tiles) - This includes bugs that are hard to reproduce (MoonPhaseBugs) with the genuine HeisenBugs (bugs which change when you try to track them down).


---


# Issue Tracker Use #

These are the different labels we use:

## Type of bug ##

We find it helpful to classify repeatable bugs differently to ones which are hard to repeat.  The reason is that what you need to do to solve them is very different.  Generally with a repeatable bug it is possible to get a reasonable estimate of how much effort it will take to fix.  With a MoonPhaseBug it is very hard indeed to know how long it will take to fix.  It is always a major advance when the type changes from MoonPhaseBug to RepeatableBug.

You are unlikely to see enhancement requests in this list, since we keep an organised list of feature requests in our main wiki instead.  The wiki is way better for organising the many competing ideas and suggestions.

|Type-RepeatableBug | Bug which has a clear scenario for repeating it |
|:------------------|:------------------------------------------------|
|Type-MoonPhaseBug  | Bug which can't be reproduced reliably          |
|Type-HeisenBug     | Investigating such a bug (debugging) hides it.  |
|Type-SummaryIssue  | An issue used to co-ordinate sub-issues         |
|Type-Enhancement   | Request for enhancement                         |
|Type-Task          | Work item that doesn't change the code or docs  |
|Type-Review        | Request for a source code review                |
|Type-Other         | Some other kind of issue                        |

## Priority of bug ##

|Priority-P1 | Blocks any release |
|:-----------|:-------------------|
|Priority-P2 | Blocks a stable release |
|Priority-P3 | MUST be release noted |
|Priority-P4 | Need not be release noted |
|Priority-P5 | Just worth tracking |

## Operating System ##

In this section it is possible to use multiple labels, e.g use both Linux and OSX as labels.

|OpSys-All | Affects all operating systems |
|:---------|:------------------------------|
|OpSys-Windows | Affects Windows users         |
|OpSys-Windows7 | Affects Windows 7 users       |
|OpSys-Vista | Affects Windows Vista users   |
|OpSys-Linux | Affects Linux users           |
|OpSys-OSX | Affects Mac OS X users        |
|OpSys-Other | Affects some other operating system |

## Milestone ##
|Milestone-Expedited | We want this urgently |
|:-------------------|:----------------------|
|Milestone-Beta      | Slated for next beta release |
|Milestone-Stable    | Slated for next stable release |
|Milestone-GSoCStart | We want this done in time for next GSoC |
|Milestone-Other     | No hurry on this      |

## List ##
This helps us in creating custom lists from the issue tracker.

|List-TopTwenty | The top active 'care abouts' |
|:--------------|:-----------------------------|
|List-ReleaseNotes | Bugs for the release notes page |
|List-RecentFixes | Bugs for the recently fixed page |
|List-LearnFrom | Closed issues which we should learn from |
|List-ToxicSludge | Issues which clog up the works |
|List-Other     | Issues not in a main 'List' category |

## Component ##
What part of Audacity has the problem.
|Component-UI | Issue relates to program UI |
|:------------|:----------------------------|
|Component-!AudioIO | Issue relates to Audio playing and recording |
|Component-BuiltInFx | Issue relates to one or more built in effects |
|Component-Nyquist | Issue relates to Nyquist Lisp interpreter |
|Component-Formats | Issue relates to exporting/importing audio data |
|Component-LADSPA | Issue relates to LADSPA plug-ins |
|Component-VAMP | Issue relates to VAMP analysis plug-ins |
|Component-Installer | Issue relates to installer code |
|Component-Labels | Issue relates to Labels     |
|Component-Envelopes | Issue relates to Envelopes  |
|Component-Multiclip | Issue relates to MultiClip  |
|Component-Scripts | Utility and installation scripts |
|Component-Docs | Issue relates to end-user documentation |
|Component-Other | Issue relates to some other component |

## Tags ##
Individual tags (these appear in green in the tracker).
|Accessibility | Particularly Affects VI users |
|:-------------|:------------------------------|
|Security      | Security risk to users        |
|Performance   | Performance issue             |
|Usability     | Affects program usability     |
|Maintainability | Hinders future changes        |
|Regression    | This was working in an earlier version |



---



# Issue Tracker Status #

Using Google's issue tracker is a discarded experiment.  The live tracker is our  [bugzilla](http://wiki.audacityteam.org/index.php?title=Bug_Lists).  The real tracker has many more issues and discussions thereon.