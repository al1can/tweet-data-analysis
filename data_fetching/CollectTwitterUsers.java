public class CollectTwitterUsers {
	private static final int SEARCH_CALL_DELAY = 5*1000;
	private static final int MAX_TRENDS = 50;
	private static final int MAX_TWEETS_PER_SEARCH = 100;
	private static final int NUM_PAGES = 5;

	public static void main(String[] args) throws IOException, InterruptedException, TwitterException, SQLException  {
		if (args.length < 4 ) {
			throw new IllegalArgumentException();
		}
    		String jdbcURL = args[0];
		String locName = args[1];
		String lang = args[2];
		
    		String[] propertiesFiles = Arrays.copyOfRange(args, 3, args.length);
    		ConfigurationBuilder[] configs  = TwitterConfigFactory.create(propertiesFiles);

		FriendsFollowersFutureData dataAdapter = new FriendsFollowersSQLFutureData(jdbcURL);
		System.out.println("*** Initial users ***");
		new CollectTwitterUsers().run(dataAdapter, configs, MAX_TWEETS_PER_SEARCH, NUM_PAGES, locName, lang);
	}
	
	private void run(FriendsFollowersFutureData dataAdapter, ConfigurationBuilder[] configs , int maxTweets, int numPages, 
			String locName, String lang) throws InterruptedException, TwitterException {
		
		ExecutorService exec = Executors.newCachedThreadPool();
		BlockingQueue<Trend> trendsQueue = new LinkedBlockingQueue<>();

		List<Twitter> twitters = new ArrayList<>();
		for ( var config : configs) {
	        	Twitter twitter = new TwitterFactory(config.build()).getInstance();		
	        	twitters.add(twitter);
	    	}	

		List<Trend> trends = this.getTrends(twitters.get(0), locName);
		trendsQueue.addAll(trends);
		
		List<Future<Integer>> taskResults = new ArrayList<>();
		for ( var twitter : twitters) {
	        	var searchTask = new SearchTweetCallable(twitter, maxTweets, numPages, lang, trendsQueue, 
	        		users->dataAdapter.insertUsers(users));
	        
	        	taskResults.add(exec.submit(searchTask));
		}
		
		int count = 0;
		for ( var result: taskResults) {
			try {
				count += result.get();
			} catch (InterruptedException | ExecutionException e) {
				e.printStackTrace();
			}
		}
		exec.shutdown();
		exec.awaitTermination(30, TimeUnit.SECONDS);
		dataAdapter.close();
		System.out.printf("Added %,d users\n", count);
	}
	
	private List<Trend> getTrends(Twitter twitter, String locName) throws TwitterException{
        	List<Location> locations = twitter.getAvailableTrends();
      
		Location location = locations.stream().
  		filter(l->l.getName().equals(locName)).findFirst().get();

		System.out.println("Found location: " +location);
      
		Trends trends;
		trends = twitter.getPlaceTrends(location.getWoeid());
		Trend[] trendsArray = trends.getTrends();
		System.out.printf("Number of trends=%d\n", trendsArray.length);

		List<Trend> trendList = Arrays.asList(trendsArray);
		trendList.stream().forEach(trend->{
			System.out.println(String.format("%s (tweet_volume: %d)", trend.getName(), trend.getTweetVolume()));
		});
		List<Trend> shortenedTrends = trendList.stream().filter(t -> t.getTweetVolume() > 0)
				.collect(Collectors.toList());
		return shortenedTrends;
	}
}

